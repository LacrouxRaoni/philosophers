/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:19:10 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/29 17:45:40 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_philo(void)
{

}

int	main(int argc, char *argv[])
{
	t_philos	data;
	t_list		*list;

	if (argc > 3 && argc < 7)
	{
		if (check_args(argv, &data) == 1)
		{
			printf ("invalid arguments\n");
			return (1);
		}
		else
		{
			if (creat_list(&data, &list) == 1)
			{
				printf ("malloc error\n");
				return (1);
			}
			else
				init_philo();
		}
	}
	return (0);
}
