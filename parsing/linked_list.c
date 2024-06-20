/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:39:20 by mmondad           #+#    #+#             */
/*   Updated: 2024/06/20 09:32:25 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_back(t_list **list, t_list *new_node)
{
	t_list *tmp;

	tmp = *list;
	if (*list)
	{
		while ((*list)->next)
			(*list) = (*list)->next;
		(*list)->next = new_node;
		*list = tmp;
	}
	else
		(*list) = new_node;
}

void	add_back_e(t_env **list, t_env *new_node)
{
	t_env *tmp;

	tmp = *list;
	if (*list)
	{
		while ((*list)->next)
			(*list) = (*list)->next;
		(*list)->next = new_node;
		*list = tmp;
	}
	else
		(*list) = new_node;
}

void	add_back_p(t_plist **list, t_plist *new_node)
{
	t_plist *tmp;

	tmp = *list;
	if (*list)
	{
		while ((*list)->next)
			(*list) = (*list)->next;
		(*list)->next = new_node;
		*list = tmp;
	}
	else
		(*list) = new_node;
}

void	create_plist(t_info *info)
{
	t_list *lst;
	t_plist	*node;

	lst = info->list;
	while (lst)
	{
		info->i = 0;
		info->j = 0;
		p_len(info);
		node = new_pnode(info);
		while (lst && lst->type != PIPE)
		{
			if (lst->type > PIPE)
			{
				node->reds[info->i] = lst->txt;
				node->types[info->i++] = lst->type;
				node->reds[info->i] = lst->next->txt;
				node->types[info->i++] = lst->next->type;
				lst = lst->next;
			}
			else
				node->parts[info->j++] = lst->txt;
			lst = lst->next;
		}
		if (node->parts)
			node->parts[info->j] = NULL;
		if (node->reds)
			node->reds[info->i] = NULL;
		add_back_p(&info->plist, node);
		if (lst)
			lst = lst->next;
		info->lst_size++;
	}
}
