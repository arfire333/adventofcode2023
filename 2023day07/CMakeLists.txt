add_executable( 2023day07 2023day07.cpp )
target_link_libraries( 2023day07 libaoc )

add_executable( 2023day07_2 2023day07_2.cpp )
target_link_libraries( 2023day07_2 libaoc )

add_executable( test_2023day07_2
  test_2023day07_2.cpp
)
target_compile_definitions( test_2023day07_2 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day07_2
  libaoc GTest::gtest_main
)

add_test( Test2023day07 test_2023day07_2 )