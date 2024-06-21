/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-06 08:34:28 by mmondad           #+#    #+#             */
/*   Updated: 2024-06-06 08:34:28 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar(char c, t_info *info)
{
	if (c == '$' && !info->flag)
		return (1);
	else if (c != '$')
		info->flag = 1;
	else if (c == '$' && info->flag)
	{
		info->flag = 0;
		return (0);
	}
	return (1);
}

char *fake_var(t_info *info, int i)
{
	char *str;

	info->flag = 0;
	if ((info->line[i] == '\'' || info->line[i] == '\"') && !info->quotes)
	{
		info->count++;
		return (NULL);
	}
	i = 0;
	while (info->line[info->count + i] && !alpha_n(info->line[info->count + i]) && dollar(info->line[info->count + i], info))
	{
		set_val(info->line[info->count + i], info);
		i++;
	}
	info->flag = 0;
	str = malloc(i + 1);
	new_fnode(str, info);
	i = 0;
	while (info->line[info->count] && !alpha_n(info->line[info->count]) && dollar(info->line[info->count], info))
		str[i++] = info->line[info->count++];
	str[i] = '\0';
	return (str);
}

char *get_line(t_info *info, int j)
{
	int len;
	char *str;

	len = until_d(info->head_e->line + j, info);
 	str = malloc(len + 1);
	new_fnode(str, info);
	len = 0;
	info->count += j;
	while (info->head_e->line[j])
		str[len++] = info->head_e->line[j++];
 	str[len] = '\0';
	return (str);
}

char	*cmp_f(t_info *info, int i)
{
	int		j;
	int		tmp;
	t_env	*head;
	char	*str;

	tmp = i;
	head = info->head_e;
	if (!alpha_n(info->line[i]) || info->quotes == '\'')
		return (fake_var(info, i));
	while (info->head_e)
	{
		j = 0;
		i = tmp;
		while (info->line[i + j] && info->line[i + j] == info->head_e->line[j] && alpha_n(info->head_e->line[j]))
			j++;
		if ((info->head_e->line[j] == '=') && (!info->line[i + j] || !alpha_n(info->line[i + j])))
		{
			str = get_line(info, ++j);
			info->head_e = head;
			return (str);
		}
		info->head_e = info->head_e->next;
	}
	info->head_e = head;
	while (alpha_n(info->line[++info->count]));
	return (NULL);
}

char *b_dollar(t_info *info)
{
	int len;
	int i;
	char *str;

	len = until_d(info->line + info->count, info);
	str = malloc(len + 1);
	new_fnode(str, info);
	i = 0;
	while (info->line[info->count] && info->line[info->count] != '$')
		str[i++] = info->line[info->count++];
	str[i] = '\0';
	return (str);
}

char *expand(t_info *info)
{
    char *str;
    char *part;

    str = NULL;
    while (info->line[info->count])
    {
        if (info->line[info->count] == '$')
            part = cmp_f(info, info->count + 1);
        else
           part = b_dollar(info);
        str = ft_strjoin(str, part, info);
    }
	free(info->line);
    return (str);
}
 