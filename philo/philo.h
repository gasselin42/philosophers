/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:02:58 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/12 17:08:44 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_params
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long int		start_time;
	int				gameover;
	int				gameover_id;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eating;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	*fork_mutex;
	int				*queue;
	int				forks;
}		t_params;

typedef struct s_philo
{
	long int	last_meal;
	long int	last_sleep;
	int			state;
	int			id;
	int			eat_count;
	int			eating;
	t_params	*params;
}					t_philo;

int			ft_atoi(char *s);
long int	get_time(void);
void		*routine(void *philo);
void		print_changes(t_philo *philo, char *str);
void		free_all(t_philo *ph);
t_philo		*init_philos(int argc, char **argv);
void		init_threads(t_philo *philo);
int			*init_queue(int nb_philos);
void		update_queue(t_philo *ph, t_params *params);
int			check_eat_count(t_params *params);
void		unlock_forks(t_params *params);
void		ft_ending(t_philo *ph, t_params *params);

#endif