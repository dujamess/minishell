/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:59:32 by mmondad           #+#    #+#             */
/*   Updated: 2024/05/28 10:27:29 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_info	*info)
{
	t_heapnode *tmp;

	while (info->head_h)
	{
		tmp = info->head_h;
		info->head_h = info->head_h->next;
		free(tmp->data);
		free(tmp);
	}
}
