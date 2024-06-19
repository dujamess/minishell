/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:29:13 by mmondad           #+#    #+#             */
/*   Updated: 2024/06/03 14:55:05 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	len_f(char *s1, t_split *data)
{
	data->len = 0;
	while (s1[data->i] && !check_sep(s1[data->i]))
	{
		if (s1[data->i] == '\'' || s1[data->i] == '\"')
		{
			data->tmp = s1[data->i++];
			while (s1[data->i] && s1[data->i++] != data->tmp)
				data->len++;
		}
		else
		{
			data->i++;
			data->len++;
		}
	}
}

void	set_val(char c, t_info *info)
{
	if (c == '\'' && !info->quotes)
		info->quotes = '\'';
	else if (c == '\'' && info->quotes == '\'')
		info->quotes = 0;
	else if (c == '\"' && !info->quotes)
		info->quotes = '\"';
	else if (c == '\"' && info->quotes == '\"')
		info->quotes = 0;
}

int	until_d(char *str, t_info *info)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '$')
	{
		set_val(str[i], info);
		i++;
	}
	return (i);
}

void	p_len(t_info *info)
{
	t_list *lst;

	lst = info->list;
	info->reds_l = 0;
	info->parts_l = 0;
	while (lst && lst->type != PIPE)
	{
		if (lst->type > PIPE)
		{
			info->reds_l += 2;
			lst = lst->next;
		}
		else
			info->parts_l++;
		lst = lst->next;
	}
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
