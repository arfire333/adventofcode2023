add_executable( 2023day02 2023day02.cpp )

# add_executable( gui_2023day02 gui_2023day02.cpp)
# target_link_libraries( gui_2023day02 raylib)

add_executable( test_2023day02
  test_2023day02.cpp
)
target_compile_definitions( test_2023day02 PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_2023day02 
  GTest::gtest_main
)

add_test( Test2023Day02 test_2023day02 )