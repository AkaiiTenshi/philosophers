/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:57:37 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/07 19:59:29 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->nu_philo)
	{
		philo = data->philos + i;
		mutex_foo(&philo->philo_lock, DESTROY);
		mutex_foo(&data->forks[i].fork, DESTROY);
		i++;
	}
	mutex_foo(&data->data_lock, DESTROY);
	mutex_foo(&data->print_lock, DESTROY);
	free(data->philos);
	free(data->forks);
}
