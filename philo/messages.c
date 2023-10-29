/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:18:57 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/29 22:12:41 by matde-je         ###   ########.fr       */
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
	if (get_time() >= philo->time_to_die && philo->data->dead == 0)
	{
		philo->data->dead = 1;
		printf("%u %i %s\n", time, philo->id, DIE);
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	if (i == 2 && philo->data->dead == 0)
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
