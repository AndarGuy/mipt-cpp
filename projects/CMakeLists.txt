cmake_minimum_required(VERSION 3.8)
project(MIPT-CPP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

# add_subdirectory(array)
add_subdirectory(complex)
# add_subdirectory(str)
