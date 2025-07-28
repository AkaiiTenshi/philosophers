/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:59:08 by salsoysa          #+#    #+#             */
/*   Updated: 2025/07/28 22:46:58 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eating_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_get_philos_ready(philo->data);
	while(!stop_eating(philo->data))
	{
		if (philo->done)
			break ;
	}
	return (NULL);
}

int	eating(t_data *data)
{
	int	i;

	i = -1;
	if (data->nu_philo == 1)
		; // coming soon
	else
	{
		while (++i < data->nu_philo)
		{
			thread_foo(&data->philos[i].thread_i, eating_routine,
				&data->philos[i], CREATE);
		}
		data->start = get_time(MILLI_S);
		boolean_set(&data->mutex_data, true, &data->philos_r);
		i = -1;
		while (++i < data->nu_philo)
			thread_foo(&data->philos[i].thread_i, NULL, NULL, JOIN);
	}
	return (0);
}
