cmake_minimum_required(VERSION 3.8)
project(shared-pointer)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.1.0 # 2.13.8
)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main src/main.cpp)
add_executable(test_unique_pointer test/test_shared_pointer.cpp)
target_link_libraries(test_unique_pointer PRIVATE Catch2::Catch2WithMain)