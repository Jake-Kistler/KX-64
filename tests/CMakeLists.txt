add_executable(isa_tests test_sum.cpp)
target_link_libraries(isa_tests PRIVATE isa_core)

add_test(NAME isa_tests COMMAND isa_tests)