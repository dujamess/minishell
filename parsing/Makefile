# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmondad <mmondad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 18:56:53 by mmondad           #+#    #+#              #
#    Updated: 2024/05/27 14:55:37 by mmondad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
SRS = ft_split.c linked_list.c parsing.c free_memory.c print.c utils.c syntax_errors.c validators.c length.c expand.c creat_node.c
OBJCTS = $(SRS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJCTS)
	$(CC) $(CFLAGS) $(OBJCTS) -o $(NAME) -lreadline

clean :
	rm -rf $(OBJCTS)
fclean : clean
	rm -rf $(NAME)

re : fclean all
