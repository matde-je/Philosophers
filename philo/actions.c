/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:18:57 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/21 21:53:02 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(int i, t_philo *philo)
{
	unsigned int	time;
	int e;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (i == 1 && philo->data->dead == 0)
	{
		e = -1;
		while (++e < philo->data->philo_num)
		{
			pthread_mutex_lock(&philo[e].lock);
			philo[e].data->dead = 1;
			pthread_mutex_unlock(&philo[e].lock);
		}
		printf("%u %i %s\n", time, philo->id, DIE);
		pthread_mutex_unlock(&philo->data->write);
		ft_exit(philo->data);
	}
	if (i == 2)
		printf("%u %i %s\n", time, philo->id, EAT);
	else if (i == 3)
		printf("%u %i %s\n", time, philo->id, SLEEP);
	else if (i == 4)
		printf("%u %i %s\n", time, philo->id, THINK);
	else if (i == 5)
		printf("%u %i %s\n", time, philo->id, FORK);
	pthread_mutex_unlock(&philo->data->write);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	messages(5, philo);
	pthread_mutex_lock(philo->l_fork);
	messages(5, philo);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	messages(2, philo);
	philo->eat_count++;
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	messages(3, philo);
	ft_usleep(philo->data->sleep_time);
}
