/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:15:27 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/07/18 21:56:54 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_routine
{
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_die;
	int			philos;
	long int	start_meal;
	int			meals;
}	t_routine;

typedef struct s_list
{
	pthread_t		philo;
	int				id;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*print_message;
	long int		last_meal;
	t_routine		routine;
	int				*philo_is_dead;
	int				*full;
	int				full_flag;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;

typedef struct s_philos
{
	int				philos;
	int				die;
	int				eat;
	int				sleep;
	int				meals;
	int				all_full;
	pthread_mutex_t	*chopstick;
	pthread_mutex_t	print_status_mutex;
	pthread_t		checker;
	int				dead_already;
	t_list			*list;
}	t_philos;

int			check_args(char **argv, t_philos *data, int argc);
int			creat_list(t_philos *data);
void		free_list(t_philos *data);
int			ft_atoi(const char *nptr);
int			ft_isdigit(int c);
char		*ft_strchr(const char *s, int c);
long int	get_time(void);
void		print_message(char *message,
				long int now, long int start_meal, t_list *node);
void		init_forks(t_philos *data);
void		pick_forks(t_list *node, t_philos *data);
void		init_routine(t_list *node, t_philos *data);
void		init_print_mutex(t_list *node, t_philos *data);
void		*lunch(void *arg);
int			check_table(t_list *node, int i);
int			time_to_eat(t_list *node, int i);
void		time_to_sleep(t_list *node);
void		time_to_think(t_list *node);
void		*die_philo(t_list *node);
void		*is_dead(void *arg);
void		wait_thread_routines(t_list *node, t_philos *data);

#endif