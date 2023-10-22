/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:27:21 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/22 16:53:14 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *data_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) data_ptr;
	while (1)
	{
		if (philo->data->dead == 1)
			break ;
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finished >= philo->data->philo_num)
		{
			pthread_mutex_lock(&philo->lock);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->lock);
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
	return ((void *)0);
}

void	*supervisor(void *philo_ptr)
{
	t_philo			*philo;
	int				e;
	unsigned int	time;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = philo->data->death_time + get_time();
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->lock);
			break ;
		}
		if (get_time() >= philo->time_to_die && philo->eating == 0)
		{
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->lock);
			e = -1;
			while (++e < philo->data->philo_num)
			{
				pthread_mutex_lock(&philo[e].lock);
				philo[e].data->dead = 1;
				pthread_mutex_unlock(&philo[e].lock);
			}
			time = get_time() - philo->data->start_time;
			pthread_mutex_lock(&philo->data->write);
			printf("%u %i %s\n", time, philo->id, DIE);
			pthread_mutex_unlock(&philo->data->write);
		}
		pthread_mutex_unlock(&philo->lock);
		if (philo->eat_count == philo->data->meals_nb)
		{
			philo->data->finished++;
			philo->eat_count++;
		}
	}
	return ((void *)0);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->lock);
		eat(philo);
		messages(4, philo);
	}
	return ((void *)0);
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
		ft_usleep(5);
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

int	case_one(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
		return (error("thread creation error", data));
	pthread_detach(data->tid[0]);
	while (1)
	{
		if (data->dead == 1)
			break ;
		ft_usleep(0);
	}
	ft_exit(data);
	return (0);
}
