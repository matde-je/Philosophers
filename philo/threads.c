/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:34:47 by matilde           #+#    #+#             */
/*   Updated: 2023/08/30 14:44:49 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (data()->finished >= data()->philo_num)
			data()->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

// eat think routine of each philo and send to supervisor
//calculate the time to die by adding the current time because they will eat
// and it is also sent to supervisor to check if dead
//type cast to assign a value to the philo pointer variable
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	philo->time_to_die = data()->time_to_die + get_time();
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
		return (NULL);
	while (data()->dead == 0)
	{
		eat(philo);
		messages(4, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return (NULL);
	return (NULL);
}

// quando o tempo de morte for excedido e o filo n esta a comer, morre.
//se ja atingiu o max meals, mais um para os filos finished
//max meals is global, 
// philo->eat_count++; so it doesnt enter the if condition again
void	*supervisor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (data()->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
			messages(1, philo);
		if (philo->eat_count == data()->min_meals)
		{
			pthread_mutex_lock(&data()->lock);
			data()->finished++;
			philo->eat_count++;
			pthread_mutex_unlock(&data()->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	create_thread(void)
{
	pthread_t	tid;
	int			i;

	data()->start_time = get_time();
	if (data()->min_meals > 0)
		if (pthread_create(&tid, NULL, &monitor, &data()->philos[0]) != 0)
			error("Error in thread creation");
	i = -1;
	while (++i < data()->philo_num)
	{
		if (pthread_create(&data()->tid[i], NULL, &routine, &data()->philos[i]))
			error("Error in thread creation for philos");
		ft_usleep(1);
	}
	i = -1;
	while (++i < data()->philo_num)
		if (pthread_join(data()->tid[i], NULL) != 0)
			error("Error in suspending exec of thread");
	pthread_detach(tid);
}
//when a detached thread terminates, its resources are automatically released
//back to the system without the need for another thread to join with the 
//terminated thread
//void*: This indicates the return type of the function
//(*): This specifies that we are dealing with a function pointer.
//(void*): This indicates the type of the function's argument. 
