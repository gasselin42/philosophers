/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:21:07 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/12 11:15:15 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat(t_philo *ph, t_params *params)
{
	if (params->nb_philo > 1 && ph->state == 't')
	{	
		sem_wait(params->sem_forks);
		sem_wait(params->sem_forks);
		sem_wait(params->sem_eating);
		ph->eating = 1;
		print_changes(ph, "has taken a fork");
		print_changes(ph, "has taken a fork");
		print_changes(ph, "is eating");
		sem_post(params->sem_eating);
		ph->last_meal = get_time();
		(ph->eat_count)++;
		sem_post(params->sem_eat);
		ph->state = 'e';
	}
}

void	ft_sleep(t_philo *ph, t_params *params)
{
	if (ph->state == 'e' && get_time() - ph->last_meal >= params->time_to_eat)
	{
		sem_post(params->sem_forks);
		sem_post(params->sem_forks);
		ph->eating = 0;
		ph->state = 's';
		print_changes(ph, "is sleeping");
		ph->last_sleep = get_time();
	}
}

void	ft_think(t_philo *ph, t_params *params)
{
	if (ph->state == 's' && get_time()
		- ph->last_sleep >= params->time_to_sleep)
	{
		ph->state = 't';
		print_changes(ph, "is thinking");
	}
}

void	*ft_die(void *philo)
{
	t_philo		*ph;
	t_params	*pm;
	long int	time;

	ph = (t_philo *)philo;
	pm = ph->params;
	while (1)
	{
		if (ph->params->gameover == 0)
		{
			time = get_time();
			if ((pm->nb_philo == 1 && time == pm->start_time
					+ pm->time_to_die) || (!ph->eating && time
					- ph->last_meal > pm->time_to_die))
			{
				sem_wait(pm->sem_write);
				printf("%ld %d %s\n", time - pm->start_time, ph->id, "died");
				sem_post(pm->sem_die);
			}
		}
	}
	return (NULL);
}

void	routine(t_philo *ph)
{
	t_params	*params;
	pthread_t	th;

	params = ph->params;
	pthread_create(&th, NULL, ft_die, ph);
	pthread_detach(th);
	while (params->gameover == 0)
	{
		if (params->nb_philo > 1)
		{
			ft_eat(ph, params);
			if (params->must_eat_count != 0
				&& ph->eat_count >= params->must_eat_count)
			{
				while (get_time() - ph->last_meal < params->time_to_eat)
					continue ;
				sem_post(params->sem_forks);
				sem_post(params->sem_forks);
				break ;
			}
			ft_sleep(ph, params);
			ft_think(ph, params);
		}
	}
	exit(EXIT_SUCCESS);
}
