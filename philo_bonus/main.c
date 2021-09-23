/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:00:41 by gasselin          #+#    #+#             */
/*   Updated: 2021/09/23 11:01:22 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	params.forks = params.nb_philo;
	sem_unlink("/forks");
	params.semaphore = sem_open("/forks", O_CREAT, 0644, params.nb_philo);
	params.pid = malloc(sizeof(pid_t) * params.nb_philo);
	return (params);
}

void	init_forks(t_philo *philo, t_params params)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < params.nb_philo)
	{
		params.pid[i] = fork();
		if (params.pid[i] < 0)
			error_pid(philo);
		if (params.pid[i] == 0)
		{
			routine(&philo[i]);
		}
		if (i == params.nb_philo - 1)
			while (j < params.nb_philo)
				waitpid(params.pid[j++], NULL, 0);
		i++;
	}
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
	if (params.semaphore == SEM_FAILED)
		return (EXIT_FAILURE);
	philo = init_philos(argc, argv, params);
	init_forks(philo, params);
	free_all(philo);
	return (0);
}
