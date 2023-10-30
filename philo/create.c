/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:27:30 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/30 13:32:01 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_data(t_data *data, int argc, char **argv)
{
	data->philo_num = (int) ft_atoi(argv[1]);
	data->tid = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->tid)
		return (error("error in malloc of tid", data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (error("error in malloc of forks", data));
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (error("error in malloc of philos", data));
	data->death_time = (unsigned long int) ft_atoi(argv[2]);
	data->eat_time = (unsigned long int) ft_atoi(argv[3]);
	data->sleep_time = (unsigned long int) ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_nb = (int) ft_atoi(argv[5]);
	else
		data->meals_nb = -1;
	if (data->death_time > 2147483647 || data->eat_time > 2147483647 \
		|| data->sleep_time > 2147483647 || data->meals_nb > 2147483647)
	{
		error("Invalid args\n", data);
		return (1);
	}
	create_data2(data);
	return (0);
}

int	create_data2(t_data *data)
{
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->lock2, NULL);
	return (0);
}

void	create_philo_fork(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].eat_count = 0;
		data->philos[i].eating = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
	}
	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_init(&data->forks[i], NULL);
			data->philos[i].l_fork = &data->forks[i];
	i = -1;
	while (++i < data->philo_num -1)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i + 1];
	}
	data->philos[i].r_fork = &data->forks[i];
	data->philos[i].l_fork = &data->forks[0];

}

int	create_thread(t_data *data)
{
	int			i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error("error in thread creation", data));
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (error("error in suspending exec of thread", data));
	}
	return (0);
}
