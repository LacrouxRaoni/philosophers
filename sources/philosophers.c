/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:19:10 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/07/18 12:43:55 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*is_dead(void *arg)
{
	int	i;
	long int	now;
	t_philos *data;
	t_list	*node;

	data = (t_philos *)arg;
	node = data->list;
	while (1)
	{
		usleep (500);
		i = -1;
		while (++i < data->philos)
		{
			now = (get_time() - data->list->routine.start_meal);
			if (node->full_flag == 0)
			{
				if (now - node->last_meal > data->die)
				{
					print_message("died", get_time(), node->routine.start_meal, node);
					data->dead_already = 1;
				}
			}
			if (node->next != NULL)
				node = node->next;
		}
		if (data->dead_already == 1 || data->all_full == data->philos)
		{
			break ;
		}
	}
}

void	*die_philo(t_list *node)
{
	pthread_mutex_lock(node->fork_right);
	node->last_meal = get_time();
	print_message("has taken a fork", get_time(), node->routine.start_meal, node);
	usleep(node->routine.time_to_die * 1000);
	print_message("died", get_time(), node->routine.start_meal, node);
	pthread_mutex_unlock(node->fork_right);
	return (NULL);
}

void	*lunch(void *arg)
{
	t_list *node;
	int	i;
	
	i = 0;
	node = (t_list *)arg;
	if (node->routine.philos == 1)
	{
		return (die_philo(node));
	}
	else
	{
		if (node->id % 2 == 0)
			usleep(1600);
		while (1)
		{
			if (node->routine.meals == 0)
				i = 1;
			if (node->routine.meals == i || (*node->philo_is_dead) == 1)
			{
				(*node->full) += 1;
				node->full_flag = 1;
				if ((*node->philo_is_dead) == 1)
					printf ("morre philo da puta %d\n", node->id);
				else
					printf ("philo %d -comi %dx\n", node->id, i);
				break ;
			}	

			//time_to_eat
			if (node->id % 2 == 0)
			{
				pthread_mutex_lock(node->fork_right);
				print_message("has taken a fork", get_time(), node->routine.start_meal, node);
				pthread_mutex_lock(node->fork_left);
				print_message("has taken a fork", get_time(), node->routine.start_meal, node);
			}
			else
			{
				pthread_mutex_lock(node->fork_left);
				print_message("has taken a fork", get_time(), node->routine.start_meal, node);
				pthread_mutex_lock(node->fork_right);
				print_message("has taken a fork", get_time(), node->routine.start_meal, node);
			}
			node->last_meal = (get_time() - node->routine.start_meal);
			print_message("is eating", get_time(), node->routine.start_meal, node);
			usleep(node->routine.time_to_eat * 1000);
			i++;
			pthread_mutex_unlock(node->fork_left);
			pthread_mutex_unlock(node->fork_right);

			//time_to_sleep
			print_message("is sleeping", get_time(), node->routine.start_meal, node);
			usleep(node->routine.time_to_sleep * 1000);
			
			
			
			//time_to_think
			print_message("is thinking", get_time(), node->routine.start_meal, node);
			if (node->routine.time_to_die - (node->routine.time_to_eat + node->routine.time_to_sleep) > 20)
				usleep(((node->routine.time_to_die - (node->routine.time_to_eat + node->routine.time_to_sleep)) * 1000) - (20 * 1000));

		}
	}
	return (NULL);
}

static void pick_forks(t_list *node, t_philos *data)
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


void init_routine(t_list *node, t_philos *data)
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
	while (i <data->philos)
	{
		node->print_message = &data->print_status_mutex;
		if (data->philos == 1)
			break ;
		node = node->next;
		i++;
	}
}

void creat_threads(t_list *node, t_philos *data)
{
	int	i;
	
	if (data->philos == 1)
		pthread_create(&(node)->philo, NULL, lunch, node);
	else
	{
		i = -1;
		while (++i < data->philos)
		{
			pthread_create(&(node)->philo, NULL, lunch, node);
			node = node->next;	
		}
	}
}

void wait_thread_routines(t_list *node, t_philos *data)
{
	int	i;	

	if (data->philos == 1)
		pthread_join(node->philo, NULL);
	else
	{
		i = -1;
		while (++i < data->philos)
		{
			pthread_join(node->philo, NULL);
			node = node->next;
		}
	}
}

void init_philo(t_philos *data)
{
	t_list *node;
	int	i;
	
	node = data->list;
	pick_forks(node, data);
	
	init_routine(node, data);

	init_print_mutex(node, data);

	creat_threads(node, data);
	
	//check_if_it's dead
	if (data->philos > 1)
	{
		pthread_create(&data->checker, NULL, is_dead, (void *)data);
	}
	
	wait_thread_routines(node, data);
	if (data->philos > 1)
		pthread_join(data->checker, NULL);
}

void	init_forks(t_philos *data)
{
	int	i;

	data->chopstick = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philos);
	i = 0;
	while (i < data->philos)
	{
		pthread_mutex_init(&data->chopstick[i], NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philos	data;

	if (argc > 3 && argc < 7)
	{
		if (check_args(argv, &data, argc) == 1)
		{
			printf ("invalid arguments\n");
			return (1);
		}
		init_forks(&data);
		if (creat_list(&data) == 1)
		{
			printf ("malloc error\n");
			return (1);
		}
		init_philo(&data);
		free_list(&data);	
	}
	return (0);
}
