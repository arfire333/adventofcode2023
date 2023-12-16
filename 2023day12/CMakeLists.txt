add_executable( 2023day12 2023day12.cpp )
target_link_libraries( 2023day12 libaoc )

add_executable( 2023day12_2 2023day12_2.cpp )
target_link_libraries( 2023day12_2 libaoc )

add_executable( test_2023day12
  test_2023day12.cpp
)
target_compile_definitions( test_2023day12 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day12 
  libaoc GTest::gtest_main
)

add_test( Test2023day12 test_2023day12 )

add_executable( test_2023day12_2
  test_2023day12_2.cpp
)
target_compile_definitions( test_2023day12_2 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day12_2 
  libaoc GTest::gtest_main
)

add_test( Test2023day12_2 test_2023day12_2 )