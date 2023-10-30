/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:27:21 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/30 20:22:16 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo1)
{
	t_philo	*philo;

	philo = odd_wait(philo1);
	while (1)
	{
		if (check_dead(philo) == 1)
			break ;
		eat(philo);
		if (messages(4, philo) == 1)
			break ;
		if (eat_big(philo) == 1)
			break ;
		if (philo->data->meals_nb > 0)
		{
			if (meals(philo) == 1)
				break ;
		}
		if (check_dead(philo) == 1)
			break ;
	}
	return (NULL);
}

int	eat_big(t_philo *philo)
{
	if (philo->data->death_time <= philo->data->eat_time * 2)
	{
		while (1)
		{
			if (check_dead(philo) == 1)
				return (1);
		}
		return (1);
	}
	else if (philo->data->eat_time > philo->data->sleep_time \
		&& philo->data->death_time - 10 > philo->data->eat_time * 2)
		usleep((philo->data->eat_time - philo->data->sleep_time) * 1000);
	return (0);
}

int	meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock2);
	if (philo->data->finished >= philo->data->philo_num)
	{
		pthread_mutex_unlock(&philo->data->lock2);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock2);
	if (philo->eat_count == philo->data->meals_nb)
	{
		pthread_mutex_lock(&philo->data->lock2);
		philo->data->finished++;
		pthread_mutex_unlock(&philo->data->lock2);
		philo->eat_count++;
	}
	return (0);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	else if (get_time() >= philo->time_to_die && philo->data->dead == 0)
	{
		pthread_mutex_unlock(&philo->data->lock);
		messages(0, philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

t_philo	*odd_wait(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = philo->data->death_time + get_time();
	if (philo->id % 2 != 0)
	{
		messages(4, philo);
		if (philo->data->eat_time < philo->data->death_time)
			usleep((philo->data->eat_time / 2) * 1000);
		else
			usleep((philo->data->death_time / 2) * 1000);
	}
	return (philo);
}
