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

#include "../minishell.h"

void	new_fnode(void *data, t_info *info)
{
	t_heapnode *node;

	node = malloc(sizeof(t_heapnode));
 	node->data = data;
	node->next = NULL;
	add_back_h(&(info->head_h), node);
}

t_plist	*new_pnode(t_info *info)
{
	t_plist *node;

	node = malloc(sizeof (t_plist));
	new_fnode(node, info);
	node->parts = NULL;
	node->reds = NULL;
	node->parts = malloc (sizeof (char *) * (info->parts_l + 1));
	new_fnode(node->parts, info);
	if (info->reds_l)
	{
		node->reds = malloc (sizeof (char *) * (info->reds_l + 1));
		new_fnode(node->reds, info);
	}
	if (info->reds_l)
	{
		node->types = malloc(sizeof (int) * (info->reds_l));
		new_fnode(node->types, info);
	}
	node->next = NULL;
	return (node);
}

t_env	*new_node_e(t_info *info)
{
	t_env	*node;
	(void)info;
	node = malloc(sizeof(t_env));
	new_fnode(node, info);
	node->next = NULL;
	return (node);
}

void	new_node(char *str, int type, t_info *info)
{
	t_list *node;
	node = malloc(sizeof(t_list));
	new_fnode(node, info);
	node->next = NULL;
	node->type = type;
	node->txt = str;
	add_back(&info->list, node);
}