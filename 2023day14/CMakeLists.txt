add_executable( 2023day14 2023day14.cpp )
target_link_libraries( 2023day14 libaoc )

add_executable( gui_2023day14 gui_2023day14.cpp)
target_link_libraries( gui_2023day14 libaoc raylib)

add_executable( test_2023day14
  test_2023day14.cpp
)
target_compile_definitions( test_2023day14 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day14 
  libaoc GTest::gtest_main
)

add_test( Test2023day14 test_2023day14 )