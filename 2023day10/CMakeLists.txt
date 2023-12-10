add_executable( 2023day10 2023day10.cpp )
target_link_libraries( 2023day10 libaoc )

add_executable( test_2023day10
  test_2023day10.cpp
)
target_compile_definitions( test_2023day10 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day10 
  libaoc GTest::gtest_main
)

add_test( Test2023day10 test_2023day10 )