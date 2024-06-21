/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:45:31 by mmondad           #+#    #+#             */
/*   Updated: 2024/06/01 20:37:57 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *head)
{
	while (head)
	{
		printf("%s\n", head->line);
		head = head->next;
	}
}

void	print_list2(t_info info)
{
	int i;
	int	j;
	int count = 1;

	while (info.plist)
	{
		i = -1;
		j = -1;
		printf("part[%d]\n", count);
		while (info.plist->parts && info.plist->parts[++i])
			printf("[%s]\n", info.plist->parts[i]);
		while (info.plist->reds && info.plist->reds[++j])
			printf("[%s] type--> [%d]\n", info.plist->reds[j], info.plist->types[j]);
		count++;
		info.plist = info.plist->next;
	}
}

void print_list(t_info info)
{
	while (info.list)
	{
		printf("[%s] -> type = %d\n", info.list->txt ,info.list->type);
		info.list = info.list->next;
	}
}

void ft_putstr(char *str, int fd)
{
	int i;

	i = -1;
	while (str[++i])
		write(fd, str + i, 1);
}

void print_error(char *msg, int ext, int fd)
{
	ft_putstr(msg, fd);
	exit(ext);
}