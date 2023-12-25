# Advent of Code 2023
![CodeQL](https://github.com/arfire333/adventofcode2023/actions/workflows/codeql.yml/badge.svg)
![Multi PLatform Build](https://github.com/arfire333/adventofcode2023/actions/workflows/cmake-multi-platform.yml/badge.svg)
[![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=arfire333_adventofcode2023&metric=security_rating)](https://sonarcloud.io/summary/new_code?id=arfire333_adventofcode2023)
[![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=arfire333_adventofcode2023&metric=sqale_rating)](https://sonarcloud.io/summary/new_code?id=arfire333_adventofcode2023)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=arfire333_adventofcode2023&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=arfire333_adventofcode2023)
[![Lines of Code](https://sonarcloud.io/api/project_badges/measure?project=arfire333_adventofcode2023&metric=ncloc)](https://sonarcloud.io/summary/new_code?id=arfire333_adventofcode2023)
[![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=arfire333_adventofcode2023&metric=reliability_rating)](https://sonarcloud.io/summary/new_code?id=arfire333_adventofcode2023)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=arfire333_adventofcode2023&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=arfire333_adventofcode2023)
[![Vulnerabilities](https://sonarcloud.io/api/project_badges/measure?project=arfire333_adventofcode2023&metric=vulnerabilities)](https://sonarcloud.io/summary/new_code?id=arfire333_adventofcode2023)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=arfire333_adventofcode2023&metric=bugs)](https://sonarcloud.io/summary/new_code?id=arfire333_adventofcode2023)


## Dependencies
 - [CMake](https://cmake.org) - The Build System.
 - [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) - Used for launch debugging with input redirection.  
 - [GTest](https://github.com/google/googletest) - Enable option for unit testing. Probably not needed.
 - [Raylib](https://raylib.com) - A C Library for visualization.

## Quirks
- When switching between build kits, you will need to delete the build directory for GTest and Raylib.
- The 2021 stuff is a warmup.
- Days 1 to 3 and warmus from 2021 get their input different from Days 4 and beyond.  The original method used redirection to provide the input.  There are quirks with VSCode that make this less than desirable.  The build/input method of the data was revised to simplify this from a developer perspective.  The new method eliminates the need for the `launch.json` file.  Oddly enough, the Testing tab of VSCode requires one to launch a particular test in debug (not run) mode.  If you want to debug a particular test, simply select it as the CMake Tools launch target and click the debug icon there. 

## Day Notes
- Day 5 - Part 2 is less than optimal and originally took about 4-5 hours to run on an AMD Ryzen 5 5600G.  It now takes about 17 minutes which is still less than optimal but better.
- Day 22 - This is animated.  


