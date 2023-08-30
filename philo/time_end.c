/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c     	                             	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:26:18 by matilde           #+#    #+#             */
/*   Updated: 2023/07/28 17:00:10 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//convert the time to miliseconds
//use tv struct to store the seconds
unsigned int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		error("gettimeofday function failed \n");
	return ((tv.tv_sec * (unsigned long int)1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(unsigned long int time)
{
	unsigned int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}
//create a smaller time for sleeping to achieve more precise control
// over the total sleep duration

void	clear_free(void)
{
	int	i;

	i = -1;
	while (++i < data()->philo_num)
	{
		pthread_mutex_destroy(&data()->forks[i]);
		pthread_mutex_destroy(&data()->philos[i].lock);
	}
	pthread_mutex_destroy(&data()->write);
	pthread_mutex_destroy(&data()->lock);
	if (data()->tid)
		free(data()->tid);
	if (data()->forks)
		free(data()->forks);
	if (data()->philos)
		free(data()->philos);
	exit(0);
}

void	error(char *str)
{
	printf("%s\n", str);
	clear_free();
}
