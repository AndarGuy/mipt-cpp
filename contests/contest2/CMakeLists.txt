cmake_minimum_required(VERSION 3.8)

project(contest2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")

set(CMAKE_CXX_CLANG_TIDY )

file(GLOB SOURCES src/*.cpp)
foreach (target ${SOURCES})
    get_filename_component(target_name ${target} NAME_WLE)
    add_executable(${target_name} ${target})
    target_link_libraries(${target_name} LINK_PUBLIC ${Boost_LIBRARIES})
endforeach (target ${SOURCES})

