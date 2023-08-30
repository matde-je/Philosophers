/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:03:14 by matilde           #+#    #+#             */
/*   Updated: 2023/08/30 12:29:14 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//write Mutex: used to protect the console output when printing
//philo is dead but the dead flag isnt updated
void	messages(int i, t_philo *philo)
{
	unsigned int	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - data()->start_time;
	if (i == 1 && data()->dead == 0)
	{
		printf("%u %i %s\n", time, philo->id, DIE);
		data()->dead = 1;
		// ft_exit();
	}
	if (!data()->dead)
	{
		if (i == 2)
			printf("%u %i %s\n", time, philo->id, EAT);
		if (i == 3)
			printf("%u %i %s\n", time, philo->id, SLEEP);
		if (i == 4)
			printf("%u %i %s\n", time, philo->id, THINK);
		if (i == 5)
			printf("%u %i %s\n", time, philo->id, FORK);
	}
	pthread_mutex_unlock(&philo->data->write);
}

//philo->lock mutex: protect operations of each philo
void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + data()->time_to_die;
	messages(2, philo);
	philo->eat_count++;
	ft_usleep(data()->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}

//data()->lock mutex used to protect-access to shared data
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	messages(5, philo);
	pthread_mutex_lock(philo->l_fork);
	messages(5, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	messages(3, philo);
	ft_usleep(data()->sleep_time);
}
