#!/usr/bin/env python3
"""Update copyright ending year to current year across project files.

By default, this script scans text files under project root and updates lines that
look like:
    Copyright (C) 2025-2026 BlueRabbitY. All rights reserved.

If the ending year is not the current year, it is replaced with the current year.
The script then prints the list of changed files.
"""

from __future__ import annotations

import argparse
import datetime as _dt
import fnmatch
import re
import sys
from pathlib import Path
from typing import Iterable

# Matches optional comment prefixes and keeps all original spacing/prefix text.
COPYRIGHT_RE = re.compile(
    r"^(?P<prefix>.*?Copyright\s*\(C\)\s*)"
    r"(?P<start>\d{4})(?:-(?P<end>\d{4}))?"
    r"(?P<suffix>\s+BlueRabbitY\.\s+All rights reserved\..*)$"
)

DEFAULT_EXCLUDES = [
    ".git/**",
    "cmake-build-*/**",
]

# Default include all paths; binary files are filtered at read time.
DEFAULT_INCLUDES = [
    "*",
]


def parse_args() -> argparse.Namespace:
    current_year = _dt.date.today().year
    parser = argparse.ArgumentParser(
        description=(
            "Update ending copyright year to current year for BlueRabbitY headers."
        )
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=Path(__file__).resolve().parents[1],
        help="Project root to scan (default: script parent project root).",
    )
    parser.add_argument(
        "--year",
        type=int,
        nargs="?",
        const=current_year,
        default=current_year,
        help=(
            "Target ending year. If omitted (or passed as bare --year), "
            "uses current system year."
        ),
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Preview changes without writing files.",
    )
    parser.add_argument(
        "--include",
        action="append",
        default=[],
        help="Additional include glob patterns (can be repeated).",
    )
    parser.add_argument(
        "--exclude",
        action="append",
        default=[],
        help=(
            "Additional exclude glob patterns (can be repeated). "
            "Patterns from root .gitignore are also applied by default."
        ),
    )
    return parser.parse_args()


def normalize_posix(path: Path, root: Path) -> str:
    return path.resolve().relative_to(root.resolve()).as_posix()


def matches_any(path_posix: str, patterns: Iterable[str]) -> bool:
    return any(fnmatch.fnmatch(path_posix, p) for p in patterns)


def gitignore_pattern_to_globs(pattern: str) -> list[str]:
    pat = pattern.strip()
    if not pat:
        return []

    is_dir_only = pat.endswith("/")
    if is_dir_only:
        pat = pat[:-1]

    anchored = pat.startswith("/")
    pat = pat.lstrip("/")
    if not pat:
        return []

    has_slash = "/" in pat
    if anchored or has_slash:
        seeds = [pat]
    else:
        # Gitignore pattern without slash applies to any path segment.
        seeds = [pat, f"**/{pat}"]

    globs: list[str] = []
    for seed in seeds:
        globs.append(seed)
        # Directory-like patterns should also match contained files.
        if is_dir_only or not any(ch in seed for ch in "*?["):
            globs.append(f"{seed}/**")
    return globs


def load_gitignore_patterns(root: Path) -> tuple[list[str], list[str]]:
    gitignore_path = root / ".gitignore"
    if not gitignore_path.is_file():
        return [], []

    excludes: list[str] = []
    unignores: list[str] = []
    for raw_line in gitignore_path.read_text(encoding="utf-8", errors="ignore").splitlines():
        line = raw_line.strip()
        if not line or line.startswith("#"):
            continue
        if line.startswith("\\"):
            line = line[1:]

        is_unignore = line.startswith("!")
        if is_unignore:
            line = line[1:]
            if not line:
                continue

        globs = gitignore_pattern_to_globs(line)
        if is_unignore:
            unignores.extend(globs)
        else:
            excludes.extend(globs)

    return excludes, unignores


def should_scan_file(
        path: Path,
        root: Path,
        includes: list[str],
        excludes: list[str],
        unignores: list[str],
) -> bool:
    try:
        rel = normalize_posix(path, root)
    except ValueError:
        return False

    if matches_any(rel, excludes) and not matches_any(rel, unignores):
        return False

    return matches_any(path.name, includes) or matches_any(rel, includes)


def is_probably_binary(raw: bytes) -> bool:
    # Null byte is a practical cross-platform binary indicator.
    return b"\x00" in raw


def rewrite_line(line: str, target_year: int) -> tuple[str, bool]:
    m = COPYRIGHT_RE.match(line.rstrip("\r\n"))
    if not m:
        return line, False

    start = m.group("start")
    end = m.group("end")
    current_end = end if end else start
    wanted = str(target_year)

    if current_end == wanted:
        return line, False

    # Keep single-year format if originally single-year; otherwise update only range tail.
    if end:
        years = f"{start}-{wanted}"
    else:
        years = wanted

    newline = ""
    if line.endswith("\r\n"):
        newline = "\r\n"
    elif line.endswith("\n"):
        newline = "\n"

    new_line = f"{m.group('prefix')}{years}{m.group('suffix')}{newline}"
    return new_line, True


def process_file(path: Path, target_year: int, dry_run: bool) -> bool:
    raw = path.read_bytes()
    if is_probably_binary(raw):
        return False

    try:
        text = raw.decode("utf-8")
        encoding = "utf-8"
    except UnicodeDecodeError:
        # Fallback to common Windows-compatible encoding; skip if undecodable.
        try:
            text = raw.decode("latin-1")
            encoding = "latin-1"
        except UnicodeDecodeError:
            return False

    changed_any = False
    new_lines: list[str] = []
    for line in text.splitlines(keepends=True):
        updated, changed = rewrite_line(line, target_year)
        changed_any = changed_any or changed
        new_lines.append(updated)

    if not changed_any:
        return False

    if not dry_run:
        with path.open("w", encoding=encoding, newline="") as fp:
            fp.write("".join(new_lines))
    return True


def iter_candidate_files(root: Path) -> Iterable[Path]:
    for path in root.rglob("*"):
        if path.is_file():
            yield path


def main() -> int:
    args = parse_args()
    root = args.root.resolve()

    gitignore_excludes, gitignore_unignores = load_gitignore_patterns(root)
    includes = DEFAULT_INCLUDES + args.include
    excludes = DEFAULT_EXCLUDES + gitignore_excludes + args.exclude

    changed_files: list[Path] = []
    for file_path in iter_candidate_files(root):
        if not should_scan_file(file_path, root, includes, excludes, gitignore_unignores):
            continue
        try:
            changed = process_file(file_path, args.year, args.dry_run)
        except OSError as exc:
            print(f"[warn] Skip {file_path}: {exc}", file=sys.stderr)
            continue
        if changed:
            changed_files.append(file_path)

    changed_files.sort(key=lambda p: normalize_posix(p, root))

    if changed_files:
        action = "Would update" if args.dry_run else "Updated"
        print(f"{action} {len(changed_files)} file(s):")
        for p in changed_files:
            print(normalize_posix(p, root))
    else:
        print("No files needed updates.")

    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except BrokenPipeError:
        # Allow piping to tools like head without noisy tracebacks.
        pass
