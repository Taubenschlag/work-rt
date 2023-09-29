/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:33:58 by sbocanci          #+#    #+#             */
/*   Updated: 2023/09/29 18:57:51 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	intersection_list_free(t_intersection_list **l)
{
	int	i;

	i = -1;
	while (++i < (*l)->size)
		free((*l)->list[i]);
	free((*l)->list);
	free(*l);
}

void	free_unsorted_list(int size, t_intersection_list *unsorted[size])
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (unsorted[i])
		{
			free(unsorted[i]->list);
			free(unsorted[i]);
		}
		i++;
	}
}
