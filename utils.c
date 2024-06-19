/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:37:59 by mmondad           #+#    #+#             */
/*   Updated: 2024/06/01 15:55:13 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*ss2;
	unsigned char	*ss1;

	ss1 = (unsigned char *) s1;
	ss2 = (unsigned char *) s2;
	i = 0;
	while ((ss1[i] || ss2[i]))
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(t_info *info, t_split data)
{
	char	*cpy;

	data.j = 0;
	len_f(info->line, &data);
	cpy = malloc(data.len + 1);
	if (!cpy)
		free_list(info);
	while (info->line[info->i] && !check_sep(info->line[info->i]))
	{
		if (info->line[info->i] == '\"' || info->line[info->i] == '\'')
		{
			data.tmp = info->line[info->i++];
			while (info->line[info->i] && info->line[info->i++] != data.tmp)
				cpy[data.j++] = info->line[info->i - 1];
		}
		else
			cpy[data.j++] = info->line[info->i++];
	}
	cpy[data.len] = '\0';
	return (cpy);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*point;
	size_t	i;

	point = malloc(count * size);
	if (point == 0)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		point[i] = '\0';
		i++;
	}
	return (point);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	j;

	if (s == NULL)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return ((char *)ft_calloc(1, sizeof(char)));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	j = 0;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (j < len)
	{
		str[j] = s[start + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;
	str = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = ((char *)s1)[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i + j] = ((char *)s2)[j];
		j++;
	}
	str[i + j] = 0;
	return (str);
}
