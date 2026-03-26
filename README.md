# Elink

`Elink` is a C++20 header-only library with CMake package export support, designed to be integrated via `find_package`.

## Requirements

- CMake 4.0 or newer
- A C++20-capable compiler

## Build and Install

### macOS / Linux

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --install build --prefix "$PWD/install"
```

After installation, the package configuration files are available under `install/lib/cmake/Elink`:

- `ElinkConfig.cmake`
- `ElinkConfigVersion.cmake`
- `ElinkTargets.cmake`

### Windows (Visual Studio generator)

```powershell
cmake -S . -B build
cmake --build build --config Release
cmake --install build --config Release --prefix "$PWD/install"
```

## Use Elink in Another Project

### 1) Find and link the package

```cmake
cmake_minimum_required(VERSION 4.0)
project(YourProject LANGUAGES CXX)

find_package(Elink REQUIRED)

add_executable(your_target main.cpp)
target_link_libraries(your_target PRIVATE Elink::elink)
```

### 2) Point CMake to the Elink installation prefix

Pass the installation prefix through `CMAKE_PREFIX_PATH`:

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH="/path/to/elink/install"
```

Windows example:

```powershell
cmake -S . -B build -DCMAKE_PREFIX_PATH="C:/path/to/elink/install"
```

## Maintenance

### Update copyright years

The repository includes `script/update-copyright-year.py` to check and update copyright
headers for `BlueRabbitY`. By default, it scans the project root, uses the current
system year as the target year, skips common build directories, and excludes paths
matched by the root `.gitignore`.

Common usage:

```bash
python3 script/update-copyright-year.py --dry-run
python3 script/update-copyright-year.py
python3 script/update-copyright-year.py --year 2026
```

- `--dry-run`: preview the files that would be updated without modifying them.
- `--year`: specify the target ending year explicitly. If omitted, the current year
  is used automatically.

## Notes

- Exported target name: `Elink::elink`
- Linking `Elink::elink` propagates the C++20 requirement (`cxx_std_20`) to consumers.
- Elink headers depend on Asio headers. For installed-package consumption, ensure Asio include paths are available in your consumer project environment.

