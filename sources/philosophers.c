/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:19:10 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/07/18 22:00:49 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	creat_threads(t_list *node, t_philos *data)
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

void	init_philo(t_philos *data)
{
	t_list	*node;

	node = data->list;
	pick_forks(node, data);
	init_routine(node, data);
	init_print_mutex(node, data);
	creat_threads(node, data);
	if (data->philos > 1)
		pthread_create(&data->checker, NULL, is_dead, (void *)data);
	wait_thread_routines(node, data);
	if (data->philos > 1)
		pthread_join(data->checker, NULL);
}

int	main(int argc, char *argv[])
{
	t_philos	data;

	if (argc > 4 && argc < 7)
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
