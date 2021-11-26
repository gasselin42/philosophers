/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:02:41 by gasselin          #+#    #+#             */
/*   Updated: 2021/11/18 13:27:53 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->nb_philo)
		pthread_mutex_unlock(&params->fork_mutex[i]);
}

int	*init_queue(int nb_philos)
{
	int	*queue;
	int	i;
	int	id;

	i = 0;
	id = 1;
	queue = malloc(sizeof(int) * nb_philos);
	while (id <= nb_philos)
	{
		queue[i++] = id;
		id += 2;
	}
	id = 2;
	while (id <= nb_philos)
	{
		queue[i++] = id;
		id += 2;
	}
	return (queue);
}

void	update_queue(t_philo *ph, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nb_philo - 1)
	{
		params->queue[i] = params->queue[i + 1];
		i++;
	}
	params->queue[i] = ph->id;
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

int	main(int argc, char **argv)
{
	t_philo		*philo;

	if (argc != 5 && argc != 6)
		return (printf("Error: # of args is %d, should be 5 or 6\n", argc));
	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	philo = init_philos(argc, argv);
	init_threads(philo);
	free_all(philo);
	return (0);
}
