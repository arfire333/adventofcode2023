add_executable( 2023day05 2023day05.cpp )
target_link_libraries( 2023day05 libaoc )

add_executable( gui_2023day05 gui_2023day05.cpp)
target_link_libraries( gui_2023day05 libaoc raylib)

add_executable( test_2023day05
  test_2023day05.cpp
)
target_compile_definitions( test_2023day05 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day05 
  libaoc GTest::gtest_main
)

add_test( Test2023day05 test_2023day05 )