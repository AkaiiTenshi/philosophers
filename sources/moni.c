/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moni.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:49:50 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/06 23:16:34 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	he_dead(t_philo *philo)
{
	long	t;
	long	ttd;
	long	last_meal;

	if (boolean_get(&philo->philo_lock, &philo->done))
		return (false);
	last_meal = long_get(&philo->philo_lock, &philo->last);
	if (last_meal == 0)
		return (false);
	t = get_time(MILLI_S) - last_meal;
	ttd = philo->data->ttd / 1000;
	if (t > ttd)
		return (true);
	return (false);
}

static bool	meals_check(t_data *data)
{
	int	i;
	int	finished_eating;

	i = -1;
	finished_eating = 0;
	while (++i < data->nu_philo)
	{
		if (get_meals_count(&data->philos[i]) >= data->max_meals)
			finished_eating++;
	}
	if (finished_eating == data->nu_philo)
	{
		boolean_set(&data->data_lock, true, &data->end);
		return (true);
	}
	return (false);
}

void	*moni_foo(void *info)
{
	int		i;
	t_data	*data;

	data = (t_data *)info;
	while (!threads_up(&data->data_lock, &data->nu_threads, data->nu_philo))
		;
	while (!stop_eating(data))
	{
		i = -1;
		while (++i < data->nu_philo && !stop_eating(data))
		{
			if (he_dead(data->philos + i))
			{
				boolean_set(&data->data_lock, true, &data->end);
				printfoo(DIED, data->philos + i);
				return (NULL);
			}
		}
		if (data->max_meals > 0)
		{
			if (meals_check(data))
				return (NULL);
		}
		usleep(5000);
	}
	return (NULL);
}

long	get_meals_count(t_philo *philo)
{
	return (long_get(&philo->philo_lock, &philo->nu_meals));
}
