/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:18:57 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/25 13:43:44 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	messages(int i, t_philo *philo)
{
	unsigned int	time;
	int				e;

	time = get_time() - philo->data->start_time;
	e = 1;
	pthread_mutex_lock(&philo->data->lock);
	if (i == 1 && philo->data->dead == 0)
	{
		philo->data->dead = 1;
		printf("%u %i %s\n", time, philo->id, DIE);
		e = 0;
	}
	else if (i == 2 && philo->data->dead == 0)
	{
		e = 0;
		printf("%u %i %s\n", time, philo->id, EAT);
	}
	else
		e = messages2(i, philo, time);
	pthread_mutex_unlock(&philo->data->lock);
	return (e);
}

int	messages2(int i, t_philo *philo, unsigned int time)
{
	int	e;

	e = 1;
	if (i == 3 && philo->data->dead == 0)
	{
		e = 0;
		printf("%u %i %s\n", time, philo->id, SLEEP);
	}
	else if (i == 4 && philo->data->dead == 0)
	{
		e = 0;
		printf("%u %i %s\n", time, philo->id, THINK);
	}
	else if (i == 5 && philo->data->dead == 0)
	{
		e = 0;
		printf("%u %i %s\n", time, philo->id, FORK);
	}
	return (e);
}

void	eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (messages(5, philo) == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	if (messages(5, philo) == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	if (messages(2, philo) == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	eat2(philo, 1);
}

void	eat(t_philo *philo, int odd)
{
	if (odd == 1)
		eat_odd(philo);
	else
	{
		pthread_mutex_lock(philo->l_fork);
		if (messages(5, philo) == 1)
		{
			pthread_mutex_unlock(philo->l_fork);
			return ;
		}
		pthread_mutex_lock(philo->r_fork);
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
		eat2(philo, 0);
	}
}

void	eat2(t_philo *philo, int odd)
{
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	philo->eat_count++;
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	if (odd == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	if (messages(3, philo) == 1)
		return ;
	ft_usleep(philo->data->sleep_time);
}
