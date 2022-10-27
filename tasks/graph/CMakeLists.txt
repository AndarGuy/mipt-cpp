cmake_minimum_required(VERSION 3.8)
project(graph)

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

add_executable(test_graph src/modules/graphs/arc_graph/arc_graph.cpp src/modules/graphs/matrix_graph/matrix_graph.cpp src/modules/graphs/list_graph/list_graph.cpp src/modules/graphs/set_graph/set_graph.cpp test/test_graph.cpp)
# add_executable(test_graph src/modules/graphs/arc_graph/arc_graph.cpp src/modules/graphs/matrix_graph/matrix_graph.cpp src/modules/graphs/list_graph/list_graph.cpp src/modules/graphs/set_graph/set_graph.cpp src/main.cpp)

target_link_libraries(test_graph PRIVATE Catch2::Catch2WithMain)