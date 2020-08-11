# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmartina <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/09 15:32:30 by qmartina          #+#    #+##   Updated: 202#    Updated: 2020/08/10 19:36:40 by petruha2001      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

LIBFT = libft

DIR_S = srcs

DIR_O = objs

HEADER = includes

SOURCES =       ft_printf.c\
          		ft_add_c_s_d.c\
          		add_char.c\
          		add_str.c\
          		ft_oxu.c\
          		ft_pars.c\
          		ft_pars2.c\
          		ft_pr_help.c\
          		add_buff.c\
          		add_d.c\
          		ft_itoa_base_c.c\
          		ft_add_double.c\
          		ft_okr_double.c\
          		ft_pointer.c\
          		ft_math.c\
          		ft_dtoa.c\

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p $(DIR_O)
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

norme:
	norminette ./libft/
	@echo
	norminette ./$(HEADER)/
	@echo
	norminette ./$(DIR_S)/

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all