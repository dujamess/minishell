/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:40:27 by mmondad           #+#    #+#             */
/*   Updated: 2024/06/02 11:20:19 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *line)
{
	char	tmp;
	int		i;
	int		flag;

	tmp = 0;
	i = 0;
	flag = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !flag)
		{
			tmp = line[i++];
			flag = 1;
		}
		if (line[i] && line[i] == tmp && flag)
			flag = 0;
		if (line[i])
			i++;
	}
	return (flag);
}

int check_escape(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	check_sep(char c)
{
	if (c == '<' || c == '>' || c == '|' || check_escape(c))
		return (1);
	return (0);
}

int	check_token(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	alpha_n(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if ((c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}
