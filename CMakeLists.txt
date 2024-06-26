cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

### To build the code, add the following to the end of your CMakeLists.txt file:      ###
enable_testing()

add_compile_definitions(STOP_YELLING)
include_directories(Source/Core)

set(SOURCES
  Source/Unity/Rect.cpp
  Source/Unity/Hitbox.cpp
)
add_executable(
  hello_test
  ${SOURCES}
  gtest_src/idk_cpp.cpp
  gtest_src/ut_rect.cpp
  gtest_src/ut_vector2.cpp
  gtest_src/ut_hitboxPool.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
### Congratulations! You’ve successfully built and run a test binary using GoogleTest. ###

