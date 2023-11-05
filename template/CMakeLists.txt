add_executable( template template.cpp )

add_executable( gui_template gui_template.cpp)
target_link_libraries( gui_template raylib)

add_executable( test_template
  test_template.cpp
)
target_compile_definitions( test_template PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_template 
  GTest::gtest_main
)

add_test( Template test_template )