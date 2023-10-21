/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:19:14 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/20 12:45:40 by matilde          ###   ########.fr       */
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
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (error("gettimeofday() error", NULL));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_lock(&data->philos[i].lock);
		data->philos[i].data->dead = 1;
		pthread_mutex_unlock(&data->philos[i].lock);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->write);
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
