/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:00:41 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/12 13:49:05 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	*eat_check(void *philo)
{
	t_philo		*ph;
	t_params	*params;
	int			eat_count;

	ph = (t_philo *)philo;
	params = ph->params;
	eat_count = 0;
	while (eat_count < params->nb_philo * params->must_eat_count)
	{
		sem_wait(params->sem_eat);
		if (params->gameover)
			return (NULL);
		eat_count++;
	}
	sem_post(params->sem_die);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	pthread_t	th;
	int			i;

	i = -1;
	if (argc != 5 && argc != 6)
		return (printf("Error: # of args is %d, should be 5 or 6\n", argc));
	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	philo = init_philos(argc, argv);
	if (argv[5])
		pthread_create(&th, NULL, &eat_check, philo);
	init_forks(philo);
	sem_wait(philo->params->sem_die);
	i = -1;
	philo->params->gameover = 1;
	sem_post(philo->params->sem_eat);
	while (++i < philo->params->nb_philo)
		kill(philo[i].pid, SIGKILL);
	if (argv[5])
		pthread_join(th, NULL);
	free_all(philo);
	return (0);
}
