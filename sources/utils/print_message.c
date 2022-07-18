/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:45:13 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/07/17 10:56:07 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(char *message, long int now, long int start_meal, t_list *node)
{
	pthread_mutex_lock(node->print_message);
	if ((*node->philo_is_dead) == 0)
		printf ("%ld philo %d %s\n", now - start_meal, node->id, message);
	pthread_mutex_unlock(node->print_message);
}
