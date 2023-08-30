/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:26:01 by matde-je          #+#    #+#             */
/*   Updated: 2023/08/30 13:59:38 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*data(void)
{
	static t_data	var;

	return (&var);
}

int	main(int argc, char **argv)
{
	check_args(argc, argv);
	create_data(argc, argv);
	create_thread();
	clear_free();
	return (0);
}

void	check_args(int argc, char	**argv)
{
	int	count;
	int	count2;

	if (argv[1][0] == 0 || (argc != 6 && argc != 5))
	{
		printf("Invalid args\n");
		exit(1);
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
				exit(1);
			}
		}
	}
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
