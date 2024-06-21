/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:53:20 by mmondad           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/27 16:53:28 by mmondad          ###   ########.fr       */
=======
/*   Updated: 2024/06/21 09:54:55 by khmessah         ###   ########.fr       */
>>>>>>> 85a0d01 (a)
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_type(char *token, int *type)
{
		if (ft_strcmp(token, "<<") == 0)
			*type = HEREDOC;
		else if (ft_strcmp(token, ">>") == 0)
			*type = A_RED;
		else if (ft_strcmp(token, ">")== 0)
			*type = O_RED;
		else if (ft_strcmp(token, "<")== 0)
			*type = I_RED;
		else if (ft_strcmp(token, "|")== 0)
			*type = PIPE;
		else
			*type = UNKNOWN;
}

char	*token(char *line, int *type, int *size, t_info *info)
{
	char	tmp;
	int		len;
	char	*token;
	(void)info;

	len = 0;
	tmp = line[0];
	while (tmp == line[len])
		len++;
	*size = len;
	token = malloc(len + 1);
	new_fnode(token, info);
	len = -1;
	while (tmp == line[++len])
		token[len] = line[len];
	token[len] = 0;
	init_type(token, type);
	return (token);
}

int	add_token(t_info *info)
{
	int		i;
	int		type;
	int		size;
	char	*str;
	i = 0;
	size = 0;
	while (info->line[i] && check_escape(info->line[i]))
		i++;
	if (info->line[i] && check_token(info->line[i]))
	{
		str = token(info->line + i, &type, &size, info);
		new_node(str, type, info);
	}
	while (info->line[i + size] &&  check_escape(info->line[i + size]))
		i++;
	return (size + i);
}

void	ft_split(t_info *info)
{
	t_split	data;

	data.i = 0;
	while (info->line && (*info->line))
	{
		info->i = 0;
		info->line += add_token(info);
		if (*info->line && !check_token(*info->line))
			new_node(ft_strdup(info, data), WORD, info);
		info->line += info->i;
		info->line += add_token(info);
	}
}
