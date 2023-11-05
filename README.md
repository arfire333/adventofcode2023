# Advent of Code 2023

## Dependencies
 - [CMake](https://cmake.org) - The Build System.
 - [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) - Used for launch debugging with input redirection.  
 - [GTest](https://github.com/google/googletest) - Enable option for unit testing. Probably not needed.
 - [Raylib](https://raylib.com) - A C Library for visualization.


## Quirks
- When switching between build kits, you will need to delete the build directory for GTest and Raylib.
- The `.vscode/launch.json` file is oriented towards Microsoft Visual Studio.  Extra configurations can be added
to do the same thing with other build systems such as gdb and Linux.  It is only present to reduce keystrokes during testing. :)
- The default `F5` in VSCode requires the `default build target` to be a target whose name matches the folder it is contained in. The `target to launch` can be any of the executables in the same folder.