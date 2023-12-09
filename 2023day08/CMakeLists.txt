add_executable( 2023day08 2023day08.cpp )
target_link_libraries( 2023day08 libaoc )

add_executable( test_2023day08
  test_2023day08.cpp
)
target_compile_definitions( test_2023day08 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day08 
  libaoc GTest::gtest_main
)

add_test( Test2023day08 test_2023day08 )