/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:39:22 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/07/12 10:23:51 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_list(t_philos *data)
{
	int		i;
	t_list	*node;
	t_list	*tmp;

	node = data->list;
	i = 0;
	while (i < data->philos)
	{
		tmp = node;
		node = tmp->next;
		free (tmp);
		i++;
	}
	free (data->chopstick);
}
