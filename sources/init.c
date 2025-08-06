/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:47:16 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/06 14:08:52 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_give_fork(t_philo *philo, t_fork *forks, int pos)
{
	philo->first_f = &forks[(pos + 1) % philo->data->nu_philo];
	philo->second_f = &forks[pos];
	if (philo->id % 2)
	{
		philo->first_f = &forks[pos];
		philo->second_f = &forks[(pos + 1) % philo->data->nu_philo];
	}
}

static void	ft_init_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->nu_philo)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->done = false;
		philo->nu_meals = 0;
		philo->data = data;
		mutex_foo(&philo->philo_lock, INIT); //pas oublier de check pour error ici, potentiellement je dois changer cette fonction en static int et du coup rajouter return (ft_init_philo(data); dans init
		ft_give_fork(philo, data->forks, i);
	}
}

int	init(t_data *data)
{
	int	i;

	i = -1;
	data->end = false;
	data->philos_r = false;
    data->nu_threads = 0;
	data->philos = malloc(data->nu_philo * sizeof(t_philo));
	if (!data->philos)
		return (-1);
	data->forks = malloc(data->nu_philo * sizeof(t_fork));
	if (!data->forks)
		return (ft_print_error("Failed to malloc forks"));
	if (mutex_foo(&data->data_lock, INIT))
		return (-1);
	if (mutex_foo(&data->print_lock, INIT))
		return (-1);
	while (++i < data->nu_philo)
	{
		if (mutex_foo(&data->forks[i].fork, INIT) == -1)
			return (-1);
		data->forks[i].fork_i = i;
	}
	ft_init_philo(data);
	return (0);
}
