/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 10:20:05 by gasselin          #+#    #+#             */
/*   Updated: 2021/09/23 15:05:40 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *ph, t_params *params)
{
	if (params->nb_philo > 1 && ph->state == 't'
		&& get_time() - ph->last_meal >= params->time_to_eat)
	{
		pthread_mutex_lock(&params->fork_mutex[ph->id - 1]);
		pthread_mutex_lock(&params->fork_mutex[ph->id % params->nb_philo]);
		if (params->forks[ph->id - 1]
			&& params->forks[ph->id % params->nb_philo])
		{
			params->forks[ph->id - 1] = 0;
			params->forks[ph->id % params->nb_philo] = 0;
			print_changes(ph, "has taken a fork");
			print_changes(ph, "has taken a fork");
			ph->state = 'e';
			print_changes(ph, "is eating");
			ph->last_meal = get_time();
			ph->eat_count++;
		}
		pthread_mutex_unlock(&params->fork_mutex[ph->id - 1]);
		pthread_mutex_unlock(&params->fork_mutex[ph->id % params->nb_philo]);
		if (params->must_eat_count != 0
			&& ph->eat_count == params->must_eat_count)
			params->gameover = 1;
	}
}

void	ft_sleep(t_philo *ph, t_params *params)
{
	if (ph->state == 'e' && get_time() - ph->last_meal >= params->time_to_eat)
	{
		ph->state = 's';
		print_changes(ph, "is sleeping");
		ph->last_sleep = get_time();
		params->forks[ph->id - 1] = 1;
		params->forks[ph->id % params->nb_philo] = 1;
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

void	ft_die(t_philo *ph, t_params *params)
{
	pthread_mutex_lock(params->mutex);
	if (params->gameover == 0)
	{
		if ((ph->eat_count >= 1 && get_time()
				- ph->last_meal >= params->time_to_die)
			|| (ph->eat_count == 0 && get_time()
				- params->start_time >= params->time_to_die))
		{
			params->gameover = 1;
			params->gameover_id = ph->id;
		}
	}
	pthread_mutex_unlock(params->mutex);
}

void	*routine(void *philo)
{
	t_philo		*ph;
	t_params	*params;

	ph = (t_philo *)philo;
	params = ph->params;
	while (1)
	{
		ft_eat(ph, params);
		ft_sleep(ph, params);
		ft_think(ph, params);
		if (params->gameover)
			break ;
		ft_die(ph, params);
		if (params->gameover && params->gameover_id == ph->id)
			break ;
	}
	if (params->gameover_id == ph->id)
	{
		usleep(10);
		print_changes(ph, "died");
	}
	return (NULL);
}
