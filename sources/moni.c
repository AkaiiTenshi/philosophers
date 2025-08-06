/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moni.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:49:50 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/06 14:56:18 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool he_dead(t_philo *philo)
{
    long t;
    long ttd;

    if (boolean_get(&philo->philo_lock, &philo->done))
        return (false);
    t = get_time(MILLI_S) - long_get(&philo->philo_lock, &philo->last);
    ttd = philo->data->ttd / 1000;

    if ( t > ttd)
        return (true);
    return (false);
}

void    *moni_foo(void *info)
{
    int i;
    t_data *data;

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
            }
        }
    }
    return (NULL);
}
