add_executable( template template.cpp )
target_link_libraries( template libaoc )

add_executable( gui_template gui_template.cpp)
target_link_libraries( gui_template libaoc raylib)

add_executable( test_template
  test_template.cpp
)
target_compile_definitions( test_template PRIVATE EXCLUDE_MAIN )

target_link_libraries( test_template 
  libaoc GTest::gtest_main
)

add_test( Testtemplate test_template )