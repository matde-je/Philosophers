/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:18:39 by matilde           #+#    #+#             */
/*   Updated: 2023/08/30 14:45:04 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//forks: mutex
void	create_data(int ac, char **av)
{
	data()->philo_num = ft_atoi(av[1]);
	if (data()->philo_num > 200)
		error("Unsupported number of philosophers");
	data()->tid = malloc(sizeof(pthread_t) * data()->philo_num);
	if (!data()->tid)
		error("error in thread id alloc");
	data()->forks = malloc(sizeof(pthread_mutex_t) * data()->philo_num);
	if (!data()->forks)
		error("error in fork alloc");
	data()->philos = malloc(sizeof(t_philo) * data()->philo_num);
	if (!data()->philos)
		error("error in philos alloc");
	data()->time_to_die = ft_atoi(av[2]);
	data()->eat_time = ft_atoi(av[3]);
	data()->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data()->min_meals = atoi(av[5]);
	else
		data()->min_meals = -1;
	data()->dead = 0;
	data()->finished = 0;
	pthread_mutex_init(&data()->write, NULL);
	pthread_mutex_init(&data()->lock, NULL);
	init_fork();
}
//data-finished mean number of philos that ate all the number of meals yet

// philos is a pointer to an array of t_philo structures
// each t_philo structure has a pointer to a t_data structure
void	init_fork(void)
{
	int	i;

	i = -1;
	while (++i < data()->philo_num)
		pthread_mutex_init(&data()->forks[i], NULL);
	data()->philos[0].r_fork = &data()->forks[0];
	data()->philos[0].l_fork = &data()->forks[data()->philo_num -1];
	i = 0;
	while (++i < data()->philo_num)
	{
		data()->philos[i].r_fork = &data()->forks[i];
		data()->philos[i].l_fork = &data()->forks[i -1];
	}
	init_philos();
}

//eat count how many are eating
void	init_philos(void)
{
	int	i;

	i = -1;
	while (++i < data()->philo_num)
	{
		data()->philos[i].data = data();
		data()->philos[i].id = i + 1;
		data()->philos[i].time_to_die = data()->time_to_die;
		data()->philos[i].eating = 0;
		data()->philos[i].eat_count = 0;
		pthread_mutex_init(&data()->philos[i].lock, NULL);
	}
	if (data()->philo_num == 1)
		case_one();
}

void	case_one(void)
{
	data()->start_time = get_time();
	if (pthread_create(&data()->tid[0], NULL, &routine, &data()->philos[0]))
		(error("Thread error"));
	pthread_detach(data()->tid[0]);
	while (data()->dead == 0)
		ft_usleep(0);
	clear_free();
}
