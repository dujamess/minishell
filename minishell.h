/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:36:40 by mmondad           #+#    #+#             */
/*   Updated: 2024/06/19 21:57:07 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/wait.h>

# define UNKNOWN 0
# define WORD 1
# define PIPE 2
# define HEREDOC 3
# define A_RED 4
# define I_RED 5
# define O_RED 6

typedef struct s_plist
{
	char			**parts;
	char			**reds;
	int				*types;
	struct s_plist	*next;
}	t_plist;

typedef struct s_list
{
	char			*txt;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}
	t_env;
typedef struct s_heapnode
{
    void				*data;
	struct s_heapnode	*next;
}	t_heapnode;

typedef struct s_info
{
	int			i;
	int			j;
	int			parts_l;
	int			reds_l;
	char		*line;
	t_list		*list;
	t_plist		*plist;
	t_env		*head_e;
	t_heapnode	*head_h;
	char		*tmp_line;
	char		**penv;
	char		**argv;
	int			argc;
	int			count;
	int			quotes;
	int			flag;
	int			lst_size;
}	t_info;


typedef struct s_split
{
	int		i;
	int		j;
	int		len;
	char	tmp;
}	t_split;

typedef struct path
{
	char **var_path;
	char **option;
}	t_path;

typedef struct variable
{
    char *nom;
    char *valeur;
}t_variable;


		/*   length   */
void	len_f(char *s1, t_split *data);
int		ft_strlen(char *str);
int		until_d(char *str, t_info *info);
void	set_val(char c, t_info *info);
void	p_len(t_list *lst, t_info *info);

		/*   validators   */
int		check_escape(char c);
int		check_token(char c);
int		check_sep(char c);
int		check_quotes(char *line);
int		alpha_n(char c);

		/*   print   */
void	print_list2(t_info info);
void	print_list(t_info info);
void	ft_putstr(char *str, int fd);
void	print_env(t_env *head);

		/*   linked_list   */
void	add_back(t_list **list, t_list *new_node);
void	new_node(char *str, int type, t_info *info);
void	create_plist(t_info *info);
t_env	*new_node_e(t_info *info);
void	add_back_p(t_plist **list, t_plist *new_node);
void	add_back_e(t_env **list, t_env *new_node);
t_plist	*new_pnode(t_info *info);
void	add_back_h(t_heapnode **list, t_heapnode *new_node);\
void	new_fnode(void *data, t_info *info);

		/*    expand		*/
char	*expand(t_info *info);


char	*ft_strjoin(char *s1, char *s2, t_info *info);
void	ft_split(t_info *info);
int		ft_strcmp(const char *s1, const char *s2);
void	free_list(t_info	*info);
char	*ft_strdup(t_info *info, t_split data);
int		stx_errors(t_info info);

/**/

char		*builtin_pwd();
int			check_is_builtin(t_info *info);
t_variable *exec_builtin(t_variable *my_env, t_info	*info, int s);
void    	herdoc_appel(t_info *info);
void    	print_env1(t_variable *my_env);
void    	heredoc(char *av);
void    	augment_level_shlvl(t_variable *env);
t_variable *builtin_export(char **av,t_variable *env);
t_variable *builtin_unset(char **av,t_variable *env);	
void    	builtin_exit(int ac,char **av);
void    	builtin_echo(int ac,char **av);
int    		builtin_cd(int ac,char **av,t_variable *my_env);
t_variable *builtin_env(char **env);
void    	execution_cmd(int ac,t_variable *env,t_path *path,t_info	*info);
int			run_builtins(int s,char **split,t_variable *my_env);
void    	split_path(t_variable  *env,t_path *path);
t_variable split_env(char *env_line);
void		free_d(char **str);
char		*ft_strdup1(const char *s);
int			ft_atoi1(const char *str);
int 		ft_strcmp1(char *s1, char *s2);
int 		count_env1(char **env);
char		*ft_strchr1(const char *s, int c);
char		*ft_strncpy1(char *dest, char *src, unsigned int n);
int			ft_strlen1(char *str);
char		*ft_strjoin1(char *s1, char *s2);
int			ft_sep_mot1(char *str, char sep, int ptr);
char		*ft_locmot1(char *str, int *ptr, char sep);
int			ft_countr_mot1(char *s, char c);
char		**ft_split1(char *s, char c);
char		*join_commande_path1(t_path *path, char *av);
#endif