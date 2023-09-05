/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:27:28 by matilde           #+#    #+#             */
/*   Updated: 2023/09/05 16:18:48 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) == 1)
		return (1);
	if (create(&data, argc, argv) == 1)
		return (1);
	if (data.philo_num == 1)
		return (case_one(&data));
	if (thread_init(&data))
		return (1);
	ft_exit(&data);
	return (0);
}

int	check_args(int argc, char	**argv)
{
	int	count;
	int	count2;

	if (argv[1][0] == '0' || (argc != 6 && argc != 5))
	{
		printf("Invalid args\n");
		return (1);
	}
	count = 0;
	while (argv[++count])
	{
		count2 = -1;
		while (argv[count][++count2])
		{
			if (argv[count][count2] == ' ')
				count2++;
			else if ((argv[count][count2] < 48 || argv[count][count2] > 57))
			{
				printf("Invalid args\n");
				return (1);
			}
		}
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	c;
	int	s;
	int	res;

	c = 0;
	s = 1;
	res = 0;
	while (str[c] == ' ' || str[c] == '\n' || str[c] == '\t'
		|| str[c] == '\v' || str[c] == '\f' || str[c] == '\r')
		c++;
	if (str[c] == '-' || str[c] == '+')
	{
		if (str[c] == '-')
			s = -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		res = (res * 10) + (str[c] - '0');
		c++;
	}
	return (res * s);
}
