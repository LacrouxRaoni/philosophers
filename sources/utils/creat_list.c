/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:15:44 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/07/14 10:09:02 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	link_node(t_list *last, t_list *node, t_philos *data)
{
	last = data->list;
	while (last->next != NULL)
		last = last->next;
	last->next = node;
	node->previous = last;
	if (node->id == data->philos)
	{
		node->next = data->list;
		data->list->previous = node;
	}
}

int	creat_list(t_philos *data)
{
	int		i;
	t_list	*node;
	t_list	*last;

	data->list = NULL;
	node = NULL;
	last = NULL;
	i = 1;
	while (i <= data->philos)
	{
		node = (t_list *)malloc(sizeof(t_list));
		if (!node)
			return (1);
		node->id = i;
		node->last_meal = 0;
		node->meals_n = &data->all_full;
		node->fork_left = NULL;
		node->fork_right = NULL;
		node->print_message = NULL;
		node->philo_is_dead = &data->dead_already;
		node->next = NULL;
		node->previous = NULL;
		if (data->list == NULL)
			data->list = node;
		else
			link_node(last, node, data);
		i++;
	}
	return (0);
}
