/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:27:30 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/26 19:44:05 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//size of a struct is the sum of the sizes of its members
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
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->lock, NULL);
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
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->philo_num - 1];
	i = 0;
	while (++i < data->philo_num)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
	}
}

int	create(t_data *data, int argc, char **argv)
{
	if (create_data(data, argc, argv))
		return (1);
	create_philo_fork(data);
	return (0);
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
	}
	create_thread2(data, tid);
	return (0);
}
