/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:15:17 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/08 12:50:08 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_params *params)
{
	sem_unlink("/pForks");
	sem_unlink("/pWrite");
	sem_unlink("/pEat");
	sem_unlink("/pDie");
	sem_unlink("/pEating");
	params->sem_forks = sem_open("/pForks", O_CREAT, 0700, params->nb_philo);
	params->sem_write = sem_open("/pWrite", O_CREAT, 0700, 1);
	params->sem_eat = sem_open("/pEat", O_CREAT, 0700, 0);
	params->sem_die = sem_open("/pDie", O_CREAT, 0700, 0);
	params->sem_eating = sem_open("/pEating", O_CREAT, 0700, 1);
}

t_params	*init_params(int argc, char **argv)
{
	t_params	*params;
	int			i;

	i = 0;
	params = malloc(sizeof(t_params));
	params->nb_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->must_eat_count = 0;
	if (argc == 6)
		params->must_eat_count = ft_atoi(argv[5]);
	params->gameover = 0;
	params->start_time = get_time();
	init_sem(params);
	return (params);
}

t_philo	*init_philos(int argc, char **argv)
{
	int			i;
	t_philo		*philo;
	t_params	*params;

	i = 0;
	params = init_params(argc, argv);
	philo = malloc(sizeof(t_philo) * params->nb_philo);
	while (i < params->nb_philo)
	{
		philo[i].last_meal = 0;
		philo[i].last_sleep = 0;
		philo[i].id = i + 1;
		philo[i].state = 't';
		philo[i].params = params;
		i++;
	}
	return (philo);
}

void	init_forks(t_philo *philo)
{
	int			i;
	int			j;
	t_params	*params;

	i = 0;
	j = 0;
	params = philo[0].params;
	while (i < params->nb_philo)
	{
		philo[i].last_meal = get_time();
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			routine(&philo[i]);
		usleep(100);
		i++;
	}
}
