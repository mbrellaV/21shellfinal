# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmartina <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 16:01:11 by qmartina          #+#    #+#              #
#    Updated: 2019/10/17 16:01:15 by qmartina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 21t

SRC = src/main.c src/builtins/ft_echo.c src/builtins/ft_cd.c src/builtins/ft_env.c src/ft_take_arg.c src/exec/ft_fun_fork.c src/builtins/ft_echo2.c src/ft_signal.c src/lexer/lexer.c src/parser/main_parser.c src/nucleus/ft_read_8.c src/exec/ft_do_pipe.c src/nucleus/nucleus.c



OBJ		= $(SRC:.c=.o)

CFLAGS	= -Wall -Werror -Wextra

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(OBJ) -o $(NAME) -L libft/ -lft -ltermcap

all: $(NAME)

clean:
	@make -C libft/ clean
	@/bin/rm -rf $(OBJ)

fclean: clean
	@/bin/rm -rf $(NAME) $(OBJ)

re: fclean $(NAME)
