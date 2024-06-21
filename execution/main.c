/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:57:53 by mmondad           #+#    #+#             */
<<<<<<< HEAD:execution/main.c
/*   Updated: 2024/06/03 15:14:05 by mmondad          ###   ########.fr       */
=======
/*   Updated: 2024/06/21 10:17:22 by khmessah         ###   ########.fr       */
>>>>>>> 85a0d01 (a):execution/parsing.c
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*cpy_env(char **env, t_info *info)
{
	int i;
	int j;
	t_env	*node;
	t_env	*head;

	i = 0;
	head = NULL;
	while (env[i])
	{
		j = 0;
		node = new_node_e(info);
		node->line = malloc(ft_strlen(env[i]) + 1);
		new_fnode(node->line, info);
		while (env[i][j])
		{
			node->line[j] = env[i][j];
			j++;
		}
		node->line[j] = '\0';
		add_back_e(&head, node);
		i++;
	}
	return (head);
}

void init_info(int ac, char **av, char **env, t_info *info)
{
	info->argc = ac;
	info->argv = av;
	info->penv = env;
	info->count = 0;
	info->lst_size = -1;
	info->quotes = 0;
	info->head_e = cpy_env(env, info);
	info->list = NULL;
	info->plist = NULL;
}

int	parsing(t_info *info)
{
	info->line = readline ("minishell-0.0$ ");
	if (info->line)
		add_history(info->line);
	info->line = expand(info);
	info->tmp_line = info->line;
	ft_split(info);
	if (!stx_errors(*info))
	{
		create_plist(info);
<<<<<<< HEAD:execution/main.c
		//print_list2(*info);
=======
		// print_list2(*info);
>>>>>>> 85a0d01 (a):execution/parsing.c
	}
	else
		return (1);
	return (0);
}



int main(int argc, char **argv, char **penv)
{
	// int 
	t_info	info;
	t_variable *my_env = builtin_env(penv);
   	augment_level_shlvl(my_env);
	t_path *path =  malloc(sizeof(t_path));
	while (1)
	{
		init_info(argc, argv, penv, &info);
		if (!parsing(&info) && info.plist)
		{
			split_path(my_env,path);
			int s;
			s = 0;
			if (info.plist && info.plist->parts)
				while(info.plist->parts[s])
					s++;
			herdoc_appel(&info);
			if (check_is_builtin(&info) == 1)
				my_env = exec_builtin(my_env,&info,s);
			else
				execution_cmd(s,my_env,path,&info, penv);
		}
		else if (parsing(&info))
			printf("stx_error\n");
		free_list(&info);
	}
}

