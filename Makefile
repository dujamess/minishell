# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 18:56:53 by mmondad           #+#    #+#              #
#    Updated: 2024/06/19 18:01:46 by khmessah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
SRS = ft_split.c linked_list.c parsing.c free_memory.c print.c utils.c \
		syntax_errors.c validators.c length.c expand.c creat_node.c \
		builtins_util.c echo.c exit.c here_doc.c SHLVL.c unset.c cd.c \
		env.c split.c execution.c export.c pwd.c exec_builtin.c
OBJCTS = $(SRS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

all : $(NAME)

$(NAME) : $(OBJCTS)
	$(CC) $(CFLAGS) $(OBJCTS) -o $(NAME) -lreadline

clean :
	rm -rf $(OBJCTS)
fclean : clean
	rm -rf $(NAME)

re : fclean all
