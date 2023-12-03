add_executable( 2023day03 2023day03.cpp )

add_executable( gui_2023day03 gui_2023day03.cpp)
target_link_libraries( gui_2023day03 raylib)

add_executable( test_2023day03
  test_2023day03.cpp
)
target_compile_definitions( test_2023day03 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day03 
  GTest::gtest_main
)

add_test( Test2023Day03 test_2023day03 )