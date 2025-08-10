/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ready.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:02:03 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/10 08:07:29 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_philos_ready(t_data *data)
{
	while (!boolean_get(&data->data_lock, &data->philos_r))
		usleep(100);
}

void	iter_foo(pthread_mutex_t *mutex, long *nu)
{
	mutex_foo(mutex, LOCK);
	(*nu)++;
	mutex_foo(mutex, UNLOCK);
}

void	shift_philo(t_philo *philo)
{
	if (philo->data->nu_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			better_usleep(3000, philo->data);
	}
	else
	{
		if (philo->id % 2)
			thinking_routine(philo);
	}
}

bool	threads_up(pthread_mutex_t *mutex, long *threads, long nu_philo)
{
	bool	res;

	res = false;
	mutex_foo(mutex, LOCK);
	if (*threads == nu_philo)
		res = true;
	mutex_foo(mutex, UNLOCK);
	return (res);
}
