cmake_minimum_required(VERSION 3.14)
project(v0_01_qmartina C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(v0_01_qmartina
        src/main.c src/builtins/ft_echo.c src/builtins/ft_cd.c src/builtins/ft_env.c src/ft_take_arg.c src/exec/ft_fun_fork.c src/builtins/ft_echo2.c src/ft_signal.c src/ft_strjoinch_i.c src/lexer/lexer.c src/parser/main_parser.c src/nucleus/ft_read_8.c src/exec/ft_do_pipe.c src/nucleus/nucleus.c)

target_link_libraries(v0_01_qmartina ${CMAKE_SOURCE_DIR}/libft/libft.a)