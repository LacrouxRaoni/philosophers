/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:15:27 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/29 17:43:03 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philos
{
	int	philos;
	int	die;
	int	eat;
	int	sleep;
	int	time_eat;
}	t_philos;

typedef struct s_list
{
	pthread_t		philo;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;

int		check_args(char **argv, t_philos *data);
int		creat_list(t_philos *data, t_list **list);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
char	*ft_strchr(const char *s, int c);

#endif