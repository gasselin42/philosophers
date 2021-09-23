/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:02:41 by gasselin          #+#    #+#             */
/*   Updated: 2021/09/23 14:53:46 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(int argc, char **argv, t_params params)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * params.nb_philo);
	while (i < params.nb_philo)
	{
		philo[i].eat_count = 0;
		philo[i].last_meal = 0;
		philo[i].last_sleep = 0;
		philo[i].id = i + 1;
		philo[i].state = 't';
		philo[i].params = &params;
		i++;
	}
	return (philo);
}

void	init_threads(t_philo *philo)
{
	pthread_t	*thread_philos;
	int			i;

	i = 0;
	thread_philos = malloc(sizeof(pthread_t) * philo[0].params->nb_philo);
	while (i < philo[0].params->nb_philo)
	{
		pthread_create(&thread_philos[i], NULL, &routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo[0].params->nb_philo)
		pthread_join(thread_philos[i++], NULL);
	free (thread_philos);
}

int	check_args(int argc, char **argv)
{
	if (ft_atoi(argv[1]) <= 0)
		return (printf("Error: # of philosophers must be greater than 0\n"));
	if (ft_atoi(argv[2]) <= 0)
		return (printf("Error: time_to_die must be greater than 0\n"));
	if (ft_atoi(argv[3]) <= 0)
		return (printf("Error: time_to_eat must be greater than 0\n"));
	if (ft_atoi(argv[4]) <= 0)
		return (printf("Error: time_to_sleep must be greater than 0\n"));
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (printf("Error: must_eat_count must be greater than 0\n"));
	return (0);
}

t_params	init_params(int argc, char **argv)
{
	t_params	params;
	int			i;

	i = 0;
	params.nb_philo = ft_atoi(argv[1]);
	params.time_to_die = ft_atoi(argv[2]);
	params.time_to_eat = ft_atoi(argv[3]);
	params.time_to_sleep = ft_atoi(argv[4]);
	params.must_eat_count = 0;
	if (argc == 6)
		params.must_eat_count = ft_atoi(argv[5]);
	params.start_time = get_time();
	params.gameover = 0;
	params.mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&params.mutex[0], NULL);
	params.fork_mutex = malloc(sizeof(pthread_mutex_t) * params.nb_philo);
	params.forks = malloc(sizeof(int) * params.nb_philo);
	params.gameover_id = 0;
	while (i < params.nb_philo)
	{
		pthread_mutex_init(&params.fork_mutex[i], NULL);
		params.forks[i] = 1;
		i++;
	}
	return (params);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_params	params;

	if (argc != 5 && argc != 6)
		return (printf("Error: # of args is %d, should be 5 or 6\n", argc));
	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	params = init_params(argc, argv);
	philo = init_philos(argc, argv, params);
	init_threads(philo);
	free_all(philo);
	return (0);
}
