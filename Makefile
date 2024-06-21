CC = cc
NAME = minishell
SRS = parsing/ft_split.c parsing/linked_list.c parsing/free_memory.c parsing/print.c parsing/utils.c \
		parsing/syntax_errors.c parsing/validators.c parsing/length.c parsing/expand.c parsing/creat_node.c \
		execution/builtins_util.c execution/echo.c execution/exit.c execution/here_doc.c execution/SHLVL.c execution/unset.c execution/cd.c \
		execution/env.c execution/split.c execution/execution.c execution/export.c execution/pwd.c execution/exec_builtin.c execution/main.c
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