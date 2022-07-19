/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:53:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/07/19 12:16:51 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_table(t_list *node, int i)
{
	if (node->routine.meals == i || (*node->philo_is_dead) == 1)
	{
		(*node->full) += 1;
		node->full_flag = 1;
		return (1);
	}
	return (0);
}

int	time_to_eat(t_list *node, int i)
{
	if (node->id % 2 == 0)
	{
		pthread_mutex_lock(node->fork_right);
		print_message("has taken a fork",
			get_time(), node->routine.start_meal, node);
		pthread_mutex_lock(node->fork_left);
		print_message("has taken a fork",
			get_time(), node->routine.start_meal, node);
	}
	else
	{
		pthread_mutex_lock(node->fork_left);
		print_message("has taken a fork",
			get_time(), node->routine.start_meal, node);
		pthread_mutex_lock(node->fork_right);
		print_message("has taken a fork",
			get_time(), node->routine.start_meal, node);
	}
	node->last_meal = (get_time() - node->routine.start_meal);
	print_message("is eating", get_time(), node->routine.start_meal, node);
	usleep(node->routine.time_to_eat * 1000);
	i++;
	pthread_mutex_unlock(node->fork_left);
	pthread_mutex_unlock(node->fork_right);
	return (i);
}

void	time_to_sleep(t_list *node)
{
	print_message("is sleeping", get_time(), node->routine.start_meal, node);
	usleep(node->routine.time_to_sleep * 1000);
}

void	time_to_think(t_list *node)
{
	print_message("is thinking", get_time(), node->routine.start_meal, node);
	if (node->routine.time_to_die
		- (node->routine.time_to_eat + node->routine.time_to_sleep) > 10)
		usleep(((node->routine.time_to_die
					- (node->routine.time_to_eat
						+ node->routine.time_to_sleep)) * 1000) - (10 * 1000));
}

void	*lunch(void *arg)
{
	t_list	*node;
	int		i;

	i = 0;
	node = (t_list *)arg;
	if (node->routine.philos == 1)
		return (die_philo(node));
	else
	{
		if (node->id % 2 == 0)
			usleep(1600);
		while (1)
		{
			if (node->routine.meals == 0)
				i = 1;
			if (check_table(node, i) == 1)
				break ;
			i = time_to_eat(node, i);
			time_to_sleep(node);
			time_to_think(node);
		}
	}
	return (NULL);
}
