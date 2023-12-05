add_executable( 2023day04 2023day04.cpp )
target_link_libraries( 2023day04 libaoc )

add_executable( test_2023day04
  test_2023day04.cpp
)
target_compile_definitions( test_2023day04 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day04 
  libaoc
  GTest::gtest_main
)

add_test( Test2023day04 test_2023day04 )