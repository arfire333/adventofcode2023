add_executable( 2023day01 2023day01.cpp )

add_executable( test_2023day01
  test_2023day01.cpp
)
target_compile_definitions( test_2023day01 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day01 
  GTest::gtest_main
)

add_test( Test2023Day01 test_2023day01 )