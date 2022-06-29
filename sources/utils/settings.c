/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:18:11 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/29 14:18:11 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_struct(t_philos *data)
{
	data->philos = 0;
	data->die = 0;
	data->eat = 0;
	data->sleep = 0;
	data->time_eat = 0;
}

static int	check_digit(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (ft_isdigit(line[j]) == 0)
			return (1);
		j++;
	}
	return (0);
}

static int	convert_values(t_philos *data, char **argv, int i)
{
	if (i == 1)
	{
		data->philos = ft_atoi(argv[i]);
		if (data->philos == 0)
			return (1);
	}
	else if (i == 2)
		data->die = ft_atoi(argv[i]);
	else if (i == 3)
		data->eat = ft_atoi(argv[i]);
	else if (i == 4)
		data->sleep = ft_atoi(argv[i]);
	else if (i == 5)
		data->time_eat = ft_atoi(argv[i]);
	else
		return (1);
	return (0);
}

int	check_args(char **argv, t_philos *data)
{
	int	i;
	int	j;

	init_struct(data);
	i = 1;
	while (argv[i] != NULL)
	{
		if (check_digit(argv[i]) == 0)
		{	
			if (convert_values(data, argv, i) == 1)
				return (1);
		}
		else
			return (1);
		i++;
	}
	return (0);
}
