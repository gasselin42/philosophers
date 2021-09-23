/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:21:07 by gasselin          #+#    #+#             */
/*   Updated: 2021/09/23 11:26:26 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat(t_philo *ph, t_params *params)
{
	if (params->nb_philo > 1 && ph->state == 't'
		&& get_time() - ph->last_meal >= params->time_to_eat)
	{
		if (params->forks >= 2)
		{
			params->forks -= 2;
			sem_wait(params->semaphore);
			print_changes(ph, "has taken a fork");
			sem_wait(params->semaphore);
			print_changes(ph, "has taken a fork");
			ph->state = 'e';
			print_changes(ph, "is eating");
			usleep(params->time_to_sleep * 1000);
			ph->last_meal = get_time();
			ph->eat_count++;
			sem_post(params->semaphore);
			sem_post(params->semaphore);
			params->forks += 2;
		}
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
	if ((ph->eat_count >= 1 && get_time()
			- ph->last_meal >= params->time_to_die)
		|| (ph->eat_count == 0 && get_time()
			- params->start_time >= params->time_to_die))
	{
		params->gameover = 1;
		print_changes(ph, "died");
	}
}

void	*routine(t_philo *ph)
{
	t_params	*params;

	params = ph->params;
	while (1)
	{
		if (params->gameover)
			break ;
		ft_eat(ph, params);
		ft_sleep(ph, params);
		ft_think(ph, params);
		ft_die(ph, params);
	}
	return (NULL);
}
