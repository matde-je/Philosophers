/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:43:18 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/30 20:18:53 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (messages(5, philo) == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	while (1)
	{
		if (pthread_mutex_trylock(philo->r_fork) == 0)
			break ;
		else
		{
			if (check_dead(philo) == 1)
			{
				pthread_mutex_unlock(philo->l_fork);
				return ;
			}
		}
	}
	eat2(philo);
}

void	eat2(t_philo *philo)
{
	if (messages(5, philo) == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	if (messages(2, philo) == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	philo->eat_count++;
	philo->time_to_die = get_time() + philo->data->death_time;
	if (philo->data->eat_time > philo->data->death_time)
		usleep(philo->data->death_time * 1000);
	else
		usleep(philo->data->eat_time * 1000);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	eat3(philo);
}

void	eat3(t_philo *philo)
{
	if (messages(3, philo) == 1)
		return ;
	if (philo->data->sleep_time > philo->data->death_time \
		|| (philo->data->sleep_time + philo->data->eat_time) \
		> philo->data->death_time)
	{
		usleep(philo->data->death_time * 1000);
		messages(0, philo);
	}
	else
		usleep(philo->data->sleep_time * 1000);
	messages(0, philo);
}
