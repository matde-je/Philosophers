/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:19:06 by matde-je          #+#    #+#             */
/*   Updated: 2023/10/21 20:38:41 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
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
	int					eating;
	long unsigned int	time_to_die;
	pthread_mutex_t		lock;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t			*tid;
	int					philo_num;
	int					meals_nb;
	int					dead;
	int					finished;
	t_philo				*philos;
	long unsigned int	death_time;
	long unsigned int	eat_time;
	long unsigned int	sleep_time;
	long unsigned int	start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
}						t_data;

int					check_args(int argc, char	**argv);
int					ft_atoi(char *str);

void				create_philo_fork(t_data *data);
int					create_data(t_data *data, int argc, char **argv);
int					create(t_data *data, int argc, char **argv);

int					error(char *str, t_data *data);
unsigned long int	get_time(void);
int					ft_usleep(long unsigned int time);
void				ft_exit(t_data *data);

void				messages(int i, t_philo *philo);
void				eat(t_philo *philo);
void				*monitor(void *data_ptr);
void				*routine(void *philo_ptr);
void				*supervisor(void *data_ptr);
int					create_thread(t_data *data);
int					case_one(t_data *data);

#endif
