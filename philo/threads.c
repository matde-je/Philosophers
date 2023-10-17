/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:27:21 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/17 17:48:10 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *data_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) data_ptr;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

// void	*supervisor(void *philo_ptr)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *) philo_ptr;
// 	while (philo->data->dead == 0)
// 	{
// 		pthread_mutex_lock(&philo->lock);
// 		if (get_time() >= philo->time_to_die && philo->eating == 0)
// 			messages(1, philo);
// 		if (philo->eat_count == philo->data->meals_nb)
// 		{
// 			pthread_mutex_lock(&philo->data->lock);
// 			philo->data->finished++;
// 			philo->eat_count++;
// 			pthread_mutex_unlock(&philo->data->lock);
// 		}
// 		pthread_mutex_unlock(&philo->lock);
// 	}
// 	return ((void *)0);
// }

void *supervisor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
    while (1)
    {
        pthread_mutex_lock(&philo->lock);
        if (philo->data->dead == 1)
        {
            pthread_mutex_unlock(&philo->lock);
            break;
        }
        if (get_time() >= philo->time_to_die && philo->eating == 0)
        {
			pthread_mutex_unlock(&philo->lock);
            messages(1, philo);
            break;
        }
        if (philo->eat_count == philo->data->meals_nb)
        {
            philo->data->finished++;
            philo->eat_count++;
        }
        pthread_mutex_unlock(&philo->lock);
    }
    return ((void *)0);
}

// void	*routine(void *philo_ptr)
// {
// 	t_philo	*philo;
//
// 	philo = (t_philo *) philo_ptr;
// 	philo->time_to_die = philo->data->death_time + get_time();
// 	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
// 		return ((void *)1);
// 	while (philo->data->dead == 0)
// 	{
// 		eat(philo);
// 		messages(4, philo);
// 	}
// 	if (pthread_join(philo->t1, NULL))
// 		return ((void *)1);
// 	return ((void *)0);
// }

void *routine(void *philo_ptr)
{
    t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	pthread_mutex_lock(&philo->lock);
    philo->time_to_die = philo->data->death_time + get_time();
	pthread_mutex_unlock(&philo->lock);
    if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
        return ((void *)1);
    pthread_mutex_lock(&philo->lock);
    while (philo->data->dead == 0)
    {
        pthread_mutex_unlock(&philo->lock);
        eat(philo);
        messages(4, philo);
        pthread_mutex_lock(&philo->lock);
    }
    pthread_mutex_unlock(&philo->lock);
    if (pthread_join(philo->t1, NULL))
        return ((void *)1);
    return ((void *)0);
}

int	create_thread(t_data *data)
{
	int			i;
	pthread_t	tid;

	data->start_time = get_time();
	if (data->meals_nb > 0)
		if (pthread_create(&tid, NULL, &monitor, &data->philos[0]))
			return (error("error in thread creation", data));
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error("error in thread creation", data));
		ft_usleep(0);
	}
	i = -1;
	while (++i < data->philo_num)
		if (pthread_join(data->tid[i], NULL))
			return (error("error in suspending exec of thread", data));
	return (0);
}

// int	case_one(t_data *data)
// {
// 	data->start_time = get_time();
// 	if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
// 		return (error("thread creation error", data));
// 	pthread_detach(data->tid[0]);
// 	while (1)
// 	{
// 		pthread_mutex_lock(&data->dead_mutex); // Lock the mutex
// 		if (data->dead == 1)
// 		{
// 			pthread_mutex_unlock(&data->dead_mutex); // Unlock the mutex
// 			break;
// 		}
// 		pthread_mutex_unlock(&data->dead_mutex); // Unlock the mutex
// 		ft_usleep(0);
// 	}
// 	// while (data->dead == 0)
// 	// 	ft_usleep(0);
// 	ft_exit(data);
// 	return (0);
// }

int case_one(t_data *data)
{
    data->start_time = get_time();
    if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
        return (error("thread creation error", data));
    pthread_detach(data->tid[0]);
    pthread_mutex_lock(&data->philos->lock);
    while (data->dead == 0)
    {
        pthread_mutex_unlock(&data->philos->lock);
        ft_usleep(0);
        pthread_mutex_lock(&data->philos->lock);
    }
    pthread_mutex_unlock(&data->philos->lock);
    ft_exit(data);
    return (0);
}

