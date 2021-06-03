add_executable(
  fsm.tests
  fsm.tests.cpp
)
target_link_libraries(
  fsm.tests
  gtest_main
  fsm
)

include(GoogleTest)
gtest_discover_tests(fsm.tests)