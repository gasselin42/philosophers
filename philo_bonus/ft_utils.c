/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:59:07 by gasselin          #+#    #+#             */
/*   Updated: 2021/10/07 14:54:47 by gasselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	sem_wait(philo->params->sem_write);
	if (philo->params->gameover == 0)
	{
		timestamp = get_time() - philo->params->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, str);
	}
	sem_post(philo->params->sem_write);
}

void	free_all(t_philo *ph)
{
	sem_close(ph->params->sem_forks);
	sem_close(ph->params->sem_write);
	sem_close(ph->params->sem_eat);
	sem_close(ph->params->sem_die);
	sem_unlink("/pForks");
	sem_unlink("/pWrite");
	sem_unlink("/pEat");
	sem_unlink("/pDie");
	free(ph->params);
	free(ph);
}
