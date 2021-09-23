/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:02:58 by gasselin          #+#    #+#             */
/*   Updated: 2021/09/23 14:53:18 by gasselin         ###   ########.fr       */
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

# define RD		"\033[0;31m"
# define NC		"\033[0m"

typedef struct s_params
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long int		start_time;
	int				gameover;
	id_t			gameover_id;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*fork_mutex;
	int				*forks;
}		t_params;

typedef struct s_philo
{
	long int		last_meal;
	long int		last_sleep;
	int				eat_count;
	int				state;
	int				id;
	t_params		*params;
}					t_philo;

int			ft_atoi(char *s);
long int	get_time(void);
void		*routine(void *philo);
void		print_changes(t_philo *philo, char *str);
void		free_all(t_philo *ph);

#endif