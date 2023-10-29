/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:27:21 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/29 23:35:22 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_ptr)
{
	int		time;
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = philo->data->death_time + get_time();
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
		if (routine2(philo) == 1)
			break ;
		if (philo->data->eat_time > philo->data->sleep_time)
		{
			time = philo->data->eat_time - philo->data->sleep_time;
			usleep(time * 1000);
		}
	}
	return (NULL);
}

int	routine2(t_philo *philo)
{
	if (philo->data->meals_nb > 0)
	{
		pthread_mutex_lock(&philo->data->lock2);
		if (philo->data->finished >= philo->data->philo_num)
		{
			pthread_mutex_unlock(&philo->data->lock2);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->lock2);
	}
	eat(philo);
	if (messages(4, philo) == 1)
		return (1);
	if (philo->data->meals_nb > 0)
	{
		if (philo->eat_count == philo->data->meals_nb)
		{
			pthread_mutex_lock(&philo->data->lock2);
			philo->data->finished++;
			pthread_mutex_unlock(&philo->data->lock2);
			philo->eat_count++;
		}
	}
	return (0);
}
