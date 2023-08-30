/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:25:00 by matde-je          #+#    #+#             */
/*   Updated: 2023/08/30 14:44:39 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIE "died"

typedef struct s_philo
{
	struct s_data		*data;
	pthread_t			t1;
	int					id;
	int					eat_count;
	//int             	status;
	int					eating;
	unsigned long int	time_to_die;
	pthread_mutex_t		lock;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t			*tid;
	int					philo_num;
	int					min_meals;
	int					dead;
	int					finished;
	t_philo				*philos;
	unsigned long int	time_to_die;
	unsigned int		eat_time;
	unsigned int		sleep_time;
	unsigned int		start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
}	t_data;

t_data			*data(void);
void			clear_free(void);
void			create_data(int ac, char **av);
void			error(char *str);
unsigned int	get_time(void);
void			ft_usleep(unsigned long int time);
void			init_fork(void);
void			init_philos(void);
int				ft_atoi(char *str);
void			check_args(int ac, char	**av);
void			create_thread(void);
void			*supervisor(void *arg);
void			*monitor(void *arg);
void			*routine(void *arg);
void			messages(int i, t_philo *philo);
void			eat(t_philo *philo);
void			take_forks(t_philo *philo);
void			drop_forks(t_philo *philo);
void			case_one(void);

#endif