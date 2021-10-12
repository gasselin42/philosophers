/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:34:29 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/12 10:49:34 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_params
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_count;
	long int	start_time;
	int			gameover;
	sem_t		*sem_forks;
	sem_t		*sem_write;
	sem_t		*sem_eat;
	sem_t		*sem_die;
	sem_t		*sem_eating;
}		t_params;

typedef struct s_philo
{
	int			eat_count;
	long int	last_meal;
	long int	last_sleep;
	int			state;
	int			id;
	int			eating;
	pid_t		pid;
	t_params	*params;
}					t_philo;

int			ft_atoi(char *s);
long int	get_time(void);
void		routine(t_philo *ph);
void		print_changes(t_philo *philo, char *str);
void		free_all(t_philo *ph);
void		init_sem(t_params *params);
t_params	*init_params(int argc, char **argv);
t_philo		*init_philos(int argc, char **argv);
void		init_forks(t_philo *philo);

#endif