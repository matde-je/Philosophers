/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:27:21 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/24 14:20:37 by matilde          ###   ########.fr       */
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
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->philo_num)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_lock(&philo->lock);
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
			break ;
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
		{
			pthread_mutex_unlock(&philo->lock);
			messages(1, philo);
			break ;
		}
		pthread_mutex_lock(&philo->lock);
		if (philo->eat_count == philo->data->meals_nb)
		{
			philo->data->finished++;
			philo->eat_count++;
		}
		pthread_mutex_unlock(&philo->lock);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (NULL);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->dead == 1)
		{
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
		eat(philo);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->dead == 0)
		{
			messages(4, philo);
		}
		else
			break ;
		pthread_mutex_unlock(&philo->data->lock);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (NULL);
}

int	create_thread(t_data *data)
{
	int			i;
	pthread_t	tid;

	data->start_time = get_time();
	if (data->meals_nb > 0)
	{
		if (pthread_create(&tid, NULL, &monitor, &data->philos[0]))
			return (error("error in thread creation", data));
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].t1, NULL, &supervisor, \
			&data->philos[i]))
			return (error("error in thread creation", data));
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error("error in thread creation", data));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (error("error in suspending exec of thread", data));
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->philos[i].t1, NULL))
			return (error("error in suspending exec of thread", data));
	}
	if (data->meals_nb > 0)
	{
		if (pthread_join(tid, NULL))
			return (error("error in suspending exec of thread", data));
	}
	return (0);
}
