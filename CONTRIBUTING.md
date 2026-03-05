# Contributing Guide

Thank you for your interest in contributing to the `Elink` project! This guide will help you get started with
contributing code.

## Code Contribution Workflow

1. Create a new feature branch:

```bash
git checkout -b your-name/[issue-no_]your-feature-short-description

# example:
git checkout -b bluerabbity/issue123_add_new_io
# or if you are not sure about the issue number:
git checkout -b bluerabbity/add_new_io
```

2. Commit your changes:

```bash
git commit -s -m "<type>: <description>"
```

The `type` is used to specify the nature of this commit, with the following definitions:

| **type**   | **description**                                               |
|------------|---------------------------------------------------------------|
| `feat`     | **A new feature**                                             |
| `fix`      | **A bug fix**                                                 |
| `docs`     | **Documentation only changes**                                |
| `style`    | **Changes that do not affect the meaning of the code**        |
| `refactor` | **A code change that neither fixes a bug nor adds a feature** |
| `perf`     | **A code change that improves performance**                   |
| `test`     | **Adding missing tests or correcting existing tests**         |
| `build`    | **Changes to build process or tools**                         |
| `ci`       | **Changes to CI configuration files and scripts**             |
| `chore`    | **Other changes that don't modify src or test files**         |
| `revert`   | **Reverts a previous commit**                                 |

3. Before submitting your code, please ensure:

- All tests pass successfully
- The code has been properly formatted
- Relevant documentation has been updated

4. Create a Pull Request:

- Ensure the PR has a clear and descriptive title
- Link the related issue(s)
- Follow the PR template requirements

## Code Style Guidelines

- Format code using `clang-format`
- Keep functions concise

## Testing Requirements

1. Backend

- All major features must include unit tests
- Components should include basic tests
- Critical interaction logic must be covered by tests
- Test coverage should not be lower than **90%**
- Run `ElinkTestRunner` to execute tests

## Additional Guidelines

- Commit messages should be clear and meaningful
- For large features, create a design document before implementation
- Discussions can take place in [GitHub Issues](https://github.com/BluerabbitY/elink/issues)
- Feel free to ask questions if you encounter any problems
