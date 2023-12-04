add_executable( 2023day04 2023day04.cpp )

add_executable( gui_2023day04 gui_2023day04.cpp)
target_link_libraries( gui_2023day04 raylib)

add_executable( test_2023day04
  test_2023day04.cpp
)
target_compile_definitions( test_2023day04 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day04 
  GTest::gtest_main
)

add_test( Test2023day04 test_2023day04 )