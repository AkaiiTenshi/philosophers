/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:59:08 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/06 15:30:34 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking_routine(t_philo *philo, bool started)
{
    long ttt;

    if (!started)
        printfoo(THINKING, philo);
    if (philo->data->nu_philo % 2)
        return ;
    ttt = (philo->data->tte * 2) - philo->data->tts;
    if (ttt < 0)
        ttt = 0;
    better_usleep(ttt * 0.31, philo->data);
}

void    *solo(void *info)
{
    t_philo *philo;

    philo = (t_philo *)info;
    ft_get_philos_ready(philo->data);
    long_set(&philo->philo_lock, get_time(MILLI_S), &philo->last);
    iter_foo(&philo->data->data_lock, &philo->data->nu_threads);
    while (!(stop_eating(philo->data)))
        usleep(200);
    return (NULL);
}

static void	eating_routine(t_philo *philo)
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
	mutex_foo(&philo->second_f->fork, UNLOCK);
}

void	*eating_foo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_get_philos_ready(philo->data);
    long_set(&philo->philo_lock, get_time(MILLI_S), &philo->last);
    iter_foo(&philo->data->data_lock, &philo->data->nu_threads);
    shift_philo(philo);
	while (!stop_eating(philo->data))
	{
		if (philo->done)
			break ;
		eating_routine(philo);
		printfoo(SLEEPING, philo);
		better_usleep(philo->data->tts, philo->data);
		thinking_routine(philo, false);
	}
	return (NULL);
}

int	eating(t_data *data)
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
