/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:15:44 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/29 14:17:24 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	connect_node(t_list *last, t_list *node,
		t_list **list, t_philos *data)
{
	last = (*list);
	while (last->next != NULL)
		last = last->next;
	last->next = node;
	node->previous = last;
	if (node->philo == data->philos)
	{
		node->next = (*list);
		(*list)->previous = node;
	}
}

int	creat_list(t_philos *data, t_list **list)
{
	int		i;
	t_list	*node;
	t_list	*last;

	(*list) = NULL;
	node = NULL;
	i = 1;
	while (i <= data->philos)
	{
		node = (t_list *)malloc(sizeof(t_list));
		if (!node)
			return (1);
		node->philo = i;
		node->next = NULL;
		node->previous = NULL;
		if ((*list) == NULL)
			(*list) = node;
		else
			connect_node(last, node, list, data);
		i++;
	}
	return (0);
}
