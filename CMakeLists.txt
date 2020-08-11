cmake_minimum_required(VERSION 3.17)
project(ls C)

set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(./inc)
include_directories(./ft_printf/includes)

add_executable(ls
        src/additional_funcs.c
        src/complete_list.c
        src/complete_list_2.c
        src/ft_ls.c
        src/ft_strjoin_safe.c
        src/get_flags.c
        src/print_errors.c
        src/print_result.c
        src/sort.c
        src/sort_args.c)


target_link_libraries(ls ${CMAKE_SOURCE_DIR}/ft_printf/libftprintf.a)
