/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:15:44 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/07/18 21:30:36 by rruiz-la         ###   ########.fr       */
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

static void	create_node(t_list *node, int i, t_philos *data)
{
	node->id = i;
	node->last_meal = 0;
	node->full = &data->all_full;
	node->full_flag = 0;
	node->fork_left = NULL;
	node->fork_right = NULL;
	node->print_message = NULL;
	node->philo_is_dead = &data->dead_already;
	node->next = NULL;
	node->previous = NULL;
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
		create_node(node, i, data);
		if (data->list == NULL)
			data->list = node;
		else
			link_node(last, node, data);
		i++;
	}
	return (0);
}
