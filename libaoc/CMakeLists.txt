add_library( libaoc )

target_include_directories( libaoc 
  PUBLIC 
    include 
)

target_sources( libaoc 
  PUBLIC 
    include/libaoc.h
  PRIVATE 
    libaoc.cpp 
)

add_executable( test_libaoc test_libaoc.cpp )
target_link_libraries( test_libaoc libaoc GTest::gtest_main )

add_test( TestLibAOC test_libaoc )