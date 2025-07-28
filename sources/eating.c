/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:59:08 by salsoysa          #+#    #+#             */
/*   Updated: 2025/07/28 16:01:06 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *eating_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    ft_get_philos_ready(philo->data);
}

int eating(t_data *data)
{
    int i;

    i = -1;
    if (data->nu_philo == 1)
        ;//coming soon
    else
    {
        while (++i < data->nu_philo)
        {
            thread_foo(&data->philos[i].thread_i, eating_routine, &data->philos[i], CREATE);
        }
        boolean_set(&data->mutex_data, &data->philos_r, true);
    }
}
