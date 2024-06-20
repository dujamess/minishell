/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:02:07 by khmessah          #+#    #+#             */
/*   Updated: 2024/06/20 09:32:25 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	check_is_builtin(t_info *info)
{
	if ((info->plist->parts[0] && ft_strcmp(info->plist->parts[0], "pwd") == 0)
	|| (info->plist->parts[0] && ft_strcmp(info->plist->parts[0], "env") == 0)
	|| (info->plist->parts[0] && ft_strcmp(info->plist->parts[0], "echo") == 0)
	|| (info->plist->parts[0] && ft_strcmp(info->plist->parts[0], "cd") == 0)
	|| (info->plist->parts[0] && ft_strcmp(info->plist->parts[0], "exit") == 0)
	|| (info->plist->parts[0] && ft_strcmp(info->plist->parts[0],"unset") == 0)
	|| (info->plist->parts[0] && ft_strcmp(info->plist->parts[0],"export") == 0))
		return 1;
	return 0;
}
t_variable *exec_builtin(t_variable *my_env, t_info	*info, int s)
{
    if (info->plist->parts[0] && ft_strcmp(info->plist->parts[0], "pwd") == 0)
		builtin_pwd();
	else if (info->plist->parts[0] && ft_strcmp(info->plist->parts[0], "env") == 0)
		print_env1(my_env);
	else if (info->plist->parts[0]&& ft_strcmp(info->plist->parts[0], "echo") == 0)
		builtin_echo(s,info->plist->parts);
	else if (info->plist->parts[0] && ft_strcmp(info->plist->parts[0], "cd") == 0)
		builtin_cd(s,info->plist->parts,my_env);
	else if (info->plist->parts[0] && ft_strcmp(info->plist->parts[0], "exit") == 0)
		builtin_exit(s,info->plist->parts);
	else if(info->plist->parts[0] && ft_strcmp(info->plist->parts[0],"unset") == 0)
		my_env = builtin_unset(info->plist->parts,my_env);
	else if(info->plist->parts[0] && ft_strcmp(info->plist->parts[0],"export") == 0)
		my_env = builtin_export(info->plist->parts,my_env);
    return my_env;
}