/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:00:49 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/12 10:43:19 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_ending(t_philo *ph, t_params *params)
{
	if (params->gameover == 0)
	{
		pthread_mutex_lock(&params->mutex);
		if (params->nb_philo > 1)
			usleep(1000);
		params->gameover = 1;
		params->gameover_id = ph->id;
		printf("%ld %d %s\n", get_time() - params->start_time, ph->id, "died");
		unlock_forks(params);
		pthread_mutex_unlock(&params->mutex);
	}
}

t_params	*init_params(int argc, char **argv)
{
	t_params	*params;
	int			i;

	i = -1;
	params = malloc(sizeof(t_params));
	params->nb_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->must_eat_count = 0;
	if (argc == 6)
		params->must_eat_count = ft_atoi(argv[5]);
	params->start_time = get_time();
	params->gameover = 0;
	pthread_mutex_init(&params->mutex, NULL);
	pthread_mutex_init(&params->mutex_die, NULL);
	params->fork_mutex = malloc(sizeof(pthread_mutex_t) * params->nb_philo);
	params->queue = init_queue(params->nb_philo);
	params->gameover_id = 0;
	params->forks = params->nb_philo;
	while (++i < params->nb_philo)
		pthread_mutex_init(&params->fork_mutex[i], NULL);
	return (params);
}

t_philo	*init_philos(int argc, char **argv)
{
	int			i;
	t_philo		*philo;
	t_params	*params;

	i = -1;
	params = init_params(argc, argv);
	philo = (t_philo *)malloc(sizeof(t_philo) * params->nb_philo);
	while (++i < params->nb_philo)
	{
		philo[i].last_meal = 0;
		philo[i].last_sleep = 0;
		philo[i].id = i + 1;
		philo[i].state = 't';
		philo[i].eat_count = 0;
		philo[i].eating = 0;
		philo[i].params = params;
	}
	return (philo);
}

void	init_threads(t_philo *philo)
{
	pthread_t	*thread_philos;
	int			i;

	i = -1;
	thread_philos = malloc(sizeof(pthread_t) * philo->params->nb_philo);
	while (++i < philo->params->nb_philo)
		pthread_create(&thread_philos[i], NULL, &routine, &philo[i]);
	i = -1;
	while (++i < philo->params->nb_philo)
		pthread_join(thread_philos[i], NULL);
	free (thread_philos);
}
