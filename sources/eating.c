/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:59:08 by salsoysa          #+#    #+#             */
/*   Updated: 2025/07/29 14:59:45 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void eating_routine(t_philo *philo)
{
	mutex_foo(&philo->first_f->fork, LOCK);
	printfoo(TOOK_FORK1, philo);
	mutex_foo(&philo->second_f->fork, LOCK);
	printfoo(TOOK_FORK2, philo);

	long_set(&philo->philo_lock, get_time(MILLI_S), &philo->last);
	philo->nu_meals++;
	printfoo(EATING, philo);
	better_usleep(philo->data->tte, philo->data);
	if (philo->data->max_meals > 0 && philo->nu_meals == philo->data->max_meals)
		boolean_set(&philo->philo_lock, true, &philo->done);
	mutex_foo(&philo->first_f->fork, UNLOCK);
	mutex_foo(&philo->first_f->fork, UNLOCK);
}

void	*eating_foo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_get_philos_ready(philo->data);
	while(!stop_eating(philo->data))
	{
		if (philo->done)
			break ;
		printfoo(SLEEPING, philo);
		better_usleep(philo->data->tts, philo->data);
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
			thread_foo(&data->philos[i].thread_i, eating_foo,
				&data->philos[i], CREATE);
		}
		data->start = get_time(MILLI_S);
		boolean_set(&data->data_lock, true, &data->philos_r);
		i = -1;
		while (++i < data->nu_philo)
			thread_foo(&data->philos[i].thread_i, NULL, NULL, JOIN);
	}
	return (0);
}
