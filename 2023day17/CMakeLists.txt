add_executable( 2023day17 2023day17.cpp )
target_link_libraries( 2023day17 libaoc )

add_executable( gui_2023day17 gui_2023day17.cpp)
target_link_libraries( gui_2023day17 libaoc raylib)

add_executable( test_2023day17
  test_2023day17.cpp
)
target_compile_definitions( test_2023day17 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day17 
  libaoc GTest::gtest_main
)

add_test( Test2023day17 test_2023day17 )