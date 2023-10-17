/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:19:14 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/17 17:46:39 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long unsigned int time)
{
	unsigned int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}

unsigned int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday() error", NULL));
	return ((tv.tv_sec * (unsigned long int)1000) + (tv.tv_usec / 1000));
}

// void	ft_exit(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < data->philo_num)
// 	{
// 		pthread_mutex_destroy(&data->forks[i]);
// 		pthread_mutex_destroy(&data->philos[i].lock);
// 	}
// 	pthread_mutex_destroy(&data->write);
// 	pthread_mutex_destroy(&data->lock);
// 	if (data->tid)
// 		free(data->tid);
// 	if (data->forks)
// 		free(data->forks);
// 	if (data->philos)
// 		free(data->philos);
// }

// void ft_exit(t_data *data)
// {
//     int i;

//     // First, stop the supervisor threads and wait for them to finish
//     for (i = 0; i < data->philo_num; ++i) {
//         pthread_mutex_lock(&data->philos[i].lock);
//         data->philos[i].data->dead = 1;  // Set the dead flag to signal exit
//         pthread_mutex_unlock(&data->philos[i].lock);
//     }

//     for (i = 0; i < data->philo_num; ++i) {
//         pthread_join(data->philos[i].t1, NULL);
//     }

//     // Now, you can safely destroy the mutexes
//     for (i = 0; i < data->philo_num; ++i) {
//         pthread_mutex_destroy(&data->forks[i]);
//         pthread_mutex_destroy(&data->philos[i].lock);
//     }

//     pthread_mutex_destroy(&data->write);
//     pthread_mutex_destroy(&data->lock);

void ft_exit(t_data *data)
{
    int i;

    // for (i = 0; i < data->philo_num; ++i) {
    //     pthread_mutex_lock(&data->philos[i].lock);
    //     data->philos[i].data->dead = 1;
    //     pthread_mutex_unlock(&data->philos[i].lock);
    // }
	// for (i = 0; i < data->philo_num; ++i) {
	// 	pthread_join(data->philos[i].t1, NULL);
    // }
    for (i = 0; i < data->philo_num; ++i) {
        pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_lock(&data->philos[i].lock);
		pthread_mutex_unlock(&data->philos[i].lock);
        pthread_mutex_destroy(&data->philos[i].lock);
    }
	pthread_mutex_lock(&data->write);
	pthread_mutex_unlock(&data->write);
    pthread_mutex_destroy(&data->write);
    pthread_mutex_destroy(&data->lock);
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}


int	error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}
