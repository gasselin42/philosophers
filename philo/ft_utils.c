/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:40:10 by gasselin          #+#    #+#             */
/*   Updated: 2021/09/21 15:20:08 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	long	result;
	int		minus;

	result = 0;
	minus = 1;
	while ((s[0] >= 9 && s[0] <= 13) || s[0] == 32)
		s++;
	if (s[0] == '-')
		minus = minus * -1;
	if (s[0] == '-' || s[0] == '+')
		s++;
	while (s[0] >= '0' && s[0] <= '9')
	{
		result = (result * 10) + s[0] - '0';
		s++;
		if (result * minus > 2147483647 || result * minus < -2147483648)
			return (-1);
	}
	return (result * minus);
}

long int	get_time(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	print_changes(t_philo *philo, char *str)
{
	long int	timestamp;

	timestamp = get_time() - philo->params->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, str);
}

void	free_all(t_philo *ph)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(ph[0].params->mutex);
	free (ph[0].params->mutex);
	while (i < ph->params->nb_philo)
		pthread_mutex_destroy(&ph[0].params->fork_mutex[i++]);
	free (ph[0].params->fork_mutex);
	free (ph[0].params->forks);
	free (ph);
}
