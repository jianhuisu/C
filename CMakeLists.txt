cmake_minimum_required(VERSION 3.16)
project(C C)

set(CMAKE_C_STANDARD 11)

include_directories(data_structure/liner/link_list)
include_directories(data_structure/liner/queue)
include_directories(data_structure/tree/binary_tree/binary_search_tree)
include_directories(Link/share_library/stack)
include_directories(Link/static_library/stack)
include_directories(tool_makefile)

## develop demo
add_executable(test
        a_test/test.c)
