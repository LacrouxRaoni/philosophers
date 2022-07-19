/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:38:49 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/07/18 21:39:19 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_forks(t_philos *data)
{
	int	i;

	data->chopstick = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * data->philos);
	i = 0;
	while (i < data->philos)
	{
		pthread_mutex_init(&data->chopstick[i], NULL);
		i++;
	}
}

void	pick_forks(t_list *node, t_philos *data)
{
	int	i;

	i = 0;
	if (data->philos == 1)
		node->fork_right = &data->chopstick[0];
	else
	{
		while (i < data->philos)
		{
			if (i == data->philos - 1)
			{
				node->fork_left = &data->chopstick[i];
				node->fork_right = &data->chopstick[0];
			}
			else
			{
				node->fork_left = &data->chopstick[i];
				node->fork_right = &data->chopstick[i + 1];
			}
			i++;
			node = node->next;
		}
	}
}

void	init_routine(t_list *node, t_philos *data)
{
	int	i;	

	i = 0;
	while (i < data->philos)
	{
		node->routine.start_meal = get_time();
		node->routine.time_to_die = data->die;
		node->routine.time_to_eat = data->eat;
		node->routine.time_to_sleep = data->sleep;
		node->routine.philos = data->philos;
		node->routine.meals = data->meals;
		if (data->philos == 1)
			break ;
		node = node->next;
		i++;
	}
}

void	init_print_mutex(t_list *node, t_philos *data)
{
	int	i;

	pthread_mutex_init(&data->print_status_mutex, NULL);
	i = 0;
	while (i < data->philos)
	{
		node->print_message = &data->print_status_mutex;
		if (data->philos == 1)
			break ;
		node = node->next;
		i++;
	}
}
