cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cdatastructures)

enable_testing()

include(FetchContent)
# Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Raylib
find_package(raylib 4.5 QUIET) 
# If there's none, fetch and build raylib
if (NOT raylib_FOUND)   
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/4.5.0.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()


add_subdirectory( libaoc )
add_subdirectory( template )
add_subdirectory( 2021day01 )
add_subdirectory( 2021day02 )
add_subdirectory( 2021day03 )
add_subdirectory( 2023day01 )
add_subdirectory( 2023day02 )
add_subdirectory( 2023day03 )
add_subdirectory( 2023day04 )
add_subdirectory( 2023day05 )
add_subdirectory( 2023day06 )
add_subdirectory( 2023day07 )
add_subdirectory( 2023day08 )
add_subdirectory( 2023day09 )
add_subdirectory( 2023day10 )
add_subdirectory( 2023day11 )
