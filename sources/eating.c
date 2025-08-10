/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:59:08 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/07 19:57:10 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking_routine(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;
	long	thinking_time;

	printfoo(THINKING, philo);
	current_time = get_time(MILLI_S);
	time_since_last_meal = current_time - philo->last;
	thinking_time = (philo->data->ttd - time_since_last_meal - 10) / 2;
	if (thinking_time > 0 && thinking_time < philo->data->ttd / 3)
		better_usleep(thinking_time, philo->data);
}

void	*solo(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	ft_get_philos_ready(philo->data);
	long_set(&philo->philo_lock, get_time(MILLI_S), &philo->last);
	iter_foo(&philo->data->data_lock, &philo->data->nu_threads);
	printfoo(TOOK_FORK1, philo);
	while (!(stop_eating(philo->data)))
	{
		usleep(10000);
		if (get_time(MILLI_S) - philo->data->start > philo->data->ttd / 1000)
			break ;
	}
	return (NULL);
}

static void	eating_routine(t_philo *philo)
{
	mutex_foo(&philo->first_f->fork, LOCK);
	printfoo(TOOK_FORK1, philo);
	mutex_foo(&philo->second_f->fork, LOCK);
	printfoo(TOOK_FORK2, philo);
	mutex_foo(&philo->philo_lock, LOCK);
	philo->nu_meals++;
	mutex_foo(&philo->philo_lock, UNLOCK);
	printfoo(EATING, philo);
	long_set(&philo->philo_lock, get_time(MILLI_S), &philo->last);
	better_usleep(philo->data->tte, philo->data);
	long_set(&philo->philo_lock, get_time(MILLI_S), &philo->last);
	if (philo->data->max_meals > 0
		&& get_meals_count(philo) >= philo->data->max_meals)
		boolean_set(&philo->philo_lock, true, &philo->done);
	mutex_foo(&philo->first_f->fork, UNLOCK);
	mutex_foo(&philo->second_f->fork, UNLOCK);
}

void	*eating_foo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_get_philos_ready(philo->data);
	long_set(&philo->philo_lock, get_time(MILLI_S), &philo->last);
	iter_foo(&philo->data->data_lock, &philo->data->nu_threads);
	if (philo->id % 2)
		better_usleep(philo->data->tte / 2, philo->data);
	shift_philo(philo);
	while (!stop_eating(philo->data))
	{
		if (philo->done)
			break ;
		eating_routine(philo);
		printfoo(SLEEPING, philo);
		better_usleep(philo->data->tts, philo->data);
		thinking_routine(philo);
	}
	return (NULL);
}

int	dinner_table(t_data *data)
{
	int	i;

	i = -1;
	if (data->max_meals == 0)
		return (0);
	if (data->nu_philo == 1)
		thread_foo(&data->philos[0].thread_i, solo, &data->philos[0], CREATE);
	else
	{
		while (++i < data->nu_philo)
			thread_foo(&data->philos[i].thread_i, eating_foo, &data->philos[i],
				CREATE);
	}
	thread_foo(&data->moni, moni_foo, data, CREATE);
	data->start = get_time(MILLI_S);
	boolean_set(&data->data_lock, true, &data->philos_r);
	i = -1;
	while (++i < data->nu_philo)
		thread_foo(&data->philos[i].thread_i, NULL, NULL, JOIN);
	boolean_set(&data->data_lock, true, &data->end);
	thread_foo(&data->moni, NULL, NULL, JOIN);
	return (0);
}
