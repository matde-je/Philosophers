#include "philosophers.h"

t_philo 	*philo(void)
{
	static t_philo	var;

	return (&var);
}
