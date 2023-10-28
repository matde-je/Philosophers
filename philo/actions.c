/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:18:57 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/28 18:39:59 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	messages(int i, t_philo *philo)
{
	unsigned int	time;
	int				e;

	pthread_mutex_lock(&philo->data->lock);
	time = get_time() - philo->data->start_time;
	e = 1;
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
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->eat_count++;
	eat2(philo, 1);
}

void	eat_even(t_philo *philo)
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
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->eat_count++;
	eat2(philo, 0);
}

void	eat2(t_philo *philo, int odd)
{
	philo->time_to_die = get_time() + philo->data->death_time;
	pthread_mutex_unlock(&philo->lock);
	if (philo->data->eat_time > philo->data->death_time)
		ft_usleep(philo->data->death_time);
	else
		ft_usleep(philo->data->eat_time);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	if (odd == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	if (messages(3, philo) == 1)
		return ;
	if (philo->data->sleep_time > philo->data->death_time)
		ft_usleep(philo->data->death_time);
	else
		ft_usleep(philo->data->sleep_time);
}
