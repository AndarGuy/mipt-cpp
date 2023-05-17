cmake_minimum_required(VERSION 3.8)
project(imaginator)

add_subdirectory(thirdparty/Catch2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(project_imaginator_main src/main.cpp src/modules/bmp/bmp.cpp src/modules/bmp/pixel_storage/pixel_storage.cpp src/modules/bmp/headers/headers.cpp)

add_executable(project_imaginator src/modules/bmp/headers/headers.cpp src/modules/bmp/pixel_storage/pixel_storage.cpp src/modules/bmp/bmp.cpp test/general_bmp.cpp)
target_link_libraries(project_imaginator PRIVATE Catch2::Catch2WithMain)