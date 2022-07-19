/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:21:25 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/07/18 21:39:45 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_thread_routines(t_list *node, t_philos *data)
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
