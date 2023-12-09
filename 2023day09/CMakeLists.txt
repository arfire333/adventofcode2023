add_executable( 2023day09 2023day09.cpp )
target_link_libraries( 2023day09 libaoc )

add_executable( 2023day09_2 2023day09_2.cpp )
target_link_libraries( 2023day09_2 libaoc )

add_executable( test_2023day09
  test_2023day09.cpp
)
target_compile_definitions( test_2023day09 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day09 
  libaoc GTest::gtest_main
)

add_test( Test2023day09 test_2023day09 )