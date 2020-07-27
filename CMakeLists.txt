cmake_minimum_required(VERSION 3.14)
project(C C)

set(CMAKE_C_STANDARD 11)

# include_directories(data_structure/linear/link_list)
# include_directories(data_structure/linear/queue)
# include_directories(data_structure/tree/binary_tree/binary_search_tree)
# include_directories(link/share_library/stack)
# include_directories(link/static_library/stack)
include_directories(a_test)

## develop demo
add_executable(test
        a_test/tree.h
        a_test/tree.c
        a_test/test.c
        )

add_executable(main
        a_test/tree.h
        a_test/tree.c
        a_test/main.c
        )