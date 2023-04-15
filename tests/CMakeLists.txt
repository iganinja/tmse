cmake_minimum_required(VERSION 3.14)
project(TMSE_tests)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(../src)

add_subdirectory(../src ../bin)

enable_testing()

add_executable(
  TMSE_tests
  undoredostack_tests.cpp
  document_tests.cpp
)
target_link_libraries(TMSE_tests
  PRIVATE GTest::gtest_main
  PRIVATE TextEditor
)

include(GoogleTest)
gtest_discover_tests(TMSE_tests)
