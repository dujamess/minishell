/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-08 10:26:55 by mmondad           #+#    #+#             */
/*   Updated: 2024-06-08 10:26:55 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_plist	*new_pnode(t_info *info)
{
	t_plist *node;

	node = malloc(sizeof (t_plist));
	if (!node)
		free_list(info);
	node->parts = NULL;
	node->reds = NULL;
	node->parts = malloc (sizeof (char *) * (info->parts_l + 1));
	if (info->reds_l)
		node->reds = malloc (sizeof (char *) * (info->reds_l + 1));
	if (info->reds_l)
		node->types = malloc(sizeof (int) * (info->reds_l));
	if (!node->parts || !node->types)
		free_list (info);
	node->next = NULL;
	return (node);
}

t_env	*new_node_e(void)
{
	t_env	*node;
	node = malloc(sizeof(t_env));
	if (!node)
		return NULL;
	node->next = NULL;
	return (node);
}

void	new_node(char *str, int type, t_info *info)
{
	t_list *node;
	node = malloc(sizeof(t_list));
	if (!node)
		free_list(info);
	node->next = NULL;
	node->type = type;
	node->txt = str;
	add_back(&info->list, node);
}