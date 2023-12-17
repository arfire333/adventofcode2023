add_executable( 2023day13 2023day13.cpp )
target_link_libraries( 2023day13 libaoc )

add_executable( gui_2023day13 gui_2023day13.cpp)
target_link_libraries( gui_2023day13 libaoc raylib)

add_executable( test_2023day13
  test_2023day13.cpp
)
target_compile_definitions( test_2023day13 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day13 
  libaoc GTest::gtest_main
)

add_test( Test2023day13 test_2023day13 )