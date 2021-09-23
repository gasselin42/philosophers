/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:34:29 by gasselin          #+#    #+#             */
/*   Updated: 2021/09/23 11:24:51 by gasselin         ###   ########.fr       */
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

typedef struct s_params
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_count;
	long int	start_time;
	int			gameover;
	int			forks;
	pid_t		*pid;
	sem_t		*semaphore;
}		t_params;

typedef struct s_philo
{
	long int	last_meal;
	long int	last_sleep;
	int			eat_count;
	int			state;
	int			id;
	t_params	*params;
}					t_philo;

int			ft_atoi(char *s);
long int	get_time(void);
void		*routine(t_philo *ph);
void		print_changes(t_philo *philo, char *str);
void		free_all(t_philo *ph);
void		error_pid(t_philo *ph);

#endif