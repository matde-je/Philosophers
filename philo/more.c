/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:43:18 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/28 17:47:43 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo, int odd)
{
	if (odd == 1)
		eat_odd(philo);
	else
		eat_even(philo);
}

void	routine3(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		messages(4, philo);
		if (philo->data->eat_time < philo->data->death_time)
			ft_usleep(philo->data->eat_time / 2);
		else
			ft_usleep(philo->data->death_time / 2);
	}
}

int	create(t_data *data, int argc, char **argv)
{
	if (create_data(data, argc, argv))
		return (1);
	create_philo_fork(data);
	return (0);
}
