/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:27:21 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/28 19:01:46 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *data_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) data_ptr;
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->dead == 1)
			break ;
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (NULL);
}

void	*supervisor(void *philo_ptr)
{
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
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
		{
			pthread_mutex_unlock(&philo->lock);
			messages(1, philo);
			break ;
		}
		supervisor2(philo);
	}
	return (NULL);
}

void	supervisor2(t_philo *philo)
{
	if (philo->data->meals_nb > 0)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->eat_count == philo->data->meals_nb)
		{
			philo->data->finished++;
			philo->eat_count++;
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
	pthread_mutex_unlock(&philo->lock);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	routine3(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
		eat(philo, philo->id % 2);
		if (messages(4, philo) == 1)
			break ;
		routine2(philo);
	}
	return (NULL);
}

void	routine2(t_philo *philo)
{
	int	time;

	if (philo->data->eat_time > philo->data->sleep_time)
	{
		time = philo->data->eat_time - philo->data->sleep_time;
		ft_usleep(time + (time / 5));
	}
	else
	{
		if (philo->data->death_time - (philo->data->eat_time * 2) < 100)
			return ;
		else
		{
			time = philo->data->eat_time / 2;
			ft_usleep(time);
		}
	}
}
