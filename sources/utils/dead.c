/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:59:57 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/07/18 21:20:58 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_philos_heart(t_philos *data, t_list *node)
{
	long int	now;

	now = (get_time() - data->list->routine.start_meal);
	if (node->full_flag == 0)
	{
		if (now - node->last_meal > data->die)
		{
			print_message("died",
				get_time(), node->routine.start_meal, node);
			data->dead_already = 1;
		}
	}
	if (node->next != NULL)
		node = node->next;
}

void	*is_dead(void *arg)
{
	int			i;
	t_philos	*data;
	t_list		*node;

	data = (t_philos *)arg;
	node = data->list;
	while (1)
	{
		usleep (500);
		i = -1;
		while (++i < data->philos)
			check_philos_heart(data, node);
		if (data->dead_already == 1 || data->all_full == data->philos)
			return (NULL);
	}
}

void	*die_philo(t_list *node)
{
	pthread_mutex_lock(node->fork_right);
	node->last_meal = get_time();
	print_message("has taken a fork", get_time(),
		node->routine.start_meal, node);
	usleep(node->routine.time_to_die * 1000);
	print_message("died", get_time(), node->routine.start_meal, node);
	pthread_mutex_unlock(node->fork_right);
	return (NULL);
}
