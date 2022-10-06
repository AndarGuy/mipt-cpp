cmake_minimum_required(VERSION 3.8)
project(array)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.1.0 # 2.13.8
)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

add_executable(main src/main.cpp src/modules/array/array.cpp)
add_executable(test_array src/modules/array/array.cpp test/test_array.cpp)
target_link_libraries(test_array PRIVATE Catch2::Catch2WithMain)