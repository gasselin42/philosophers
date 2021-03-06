/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 10:20:05 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/18 11:47:41 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_die(t_philo *ph, t_params *params)
{
	pthread_mutex_lock(&params->mutex_die);
	if (params->gameover == 0)
	{
		if ((ph->eat_count >= 1 && !ph->eating && get_time()
				- ph->last_meal > params->time_to_die)
			|| (ph->eat_count == 0 && get_time()
				- params->start_time >= params->time_to_die))
		{
			ft_ending(ph, params);
		}
	}
	pthread_mutex_unlock(&params->mutex_die);
}

void	ft_eat(t_philo *ph, t_params *params)
{
	if (params->nb_philo > 1 && ph->state == 't')
	{
		if (ph->id == params->queue[0] && params->forks >= 2)
		{
			pthread_mutex_lock(&params->eating);
			pthread_mutex_lock(&params->fork_mutex[ph->id - 1]);
			pthread_mutex_lock(&params->fork_mutex[ph->id % params->nb_philo]);
			ph->state = 'e';
			ph->eating = 1;
			if (params->gameover)
				return ;
			print_changes(ph, "has taken a fork");
			print_changes(ph, "has taken a fork");
			print_changes(ph, "is eating");
			params->forks -= 2;
			(ph->eat_count)++;
			ph->last_meal = get_time();
			update_queue(ph, params);
			pthread_mutex_unlock(&params->eating);
		}
	}
}

void	ft_sleep(t_philo *ph, t_params *params)
{
	if (ph->state == 'e' && get_time() - ph->last_meal >= params->time_to_eat)
	{
		pthread_mutex_lock(&params->mutex);
		params->forks += 2;
		pthread_mutex_unlock(&params->mutex);
		pthread_mutex_unlock(&params->fork_mutex[ph->id - 1]);
		pthread_mutex_unlock(&params->fork_mutex[ph->id % params->nb_philo]);
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

void	*routine(void *philo)
{
	t_philo		*ph;
	t_params	*prms;

	ph = (t_philo *)philo;
	prms = ph->params;
	while (prms->gameover == 0)
	{
		ft_eat(ph, prms);
		if (prms->must_eat_count != 0
			&& ph->eat_count == prms->must_eat_count)
		{
			while (get_time() - ph->last_meal < prms->time_to_eat)
				continue ;
			pthread_mutex_unlock(&prms->fork_mutex[ph->id - 1]);
			pthread_mutex_unlock(&prms->fork_mutex[ph->id % prms->nb_philo]);
			prms->forks += 2;
			break ;
		}
		ft_sleep(ph, prms);
		ft_think(ph, prms);
		ft_die(ph, prms);
	}
	return (NULL);
}
