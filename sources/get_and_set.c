/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:29:14 by salsoysa          #+#    #+#             */
/*   Updated: 2025/07/29 16:20:59 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    long_get(pthread_mutex_t *mutex, long *change)
{
    long    fresh;
    mutex_foo(mutex, LOCK);
    fresh = *change;
    mutex_foo(mutex, UNLOCK);
    return (fresh);
}

void    long_set(pthread_mutex_t *mutex, long change, long *fresh )
{
    mutex_foo(mutex, LOCK);
    *fresh = change;
    mutex_foo(mutex, UNLOCK);
}

void    boolean_set(pthread_mutex_t *mutex, bool change, bool *fresh )
{
    mutex_foo(mutex, LOCK);
    *fresh = change;
    mutex_foo(mutex, UNLOCK);
}

bool    boolean_get(pthread_mutex_t *mutex, bool *change)
{
    bool    fresh;
    mutex_foo(mutex, LOCK);
    fresh = *change;
    mutex_foo(mutex, UNLOCK);
    return (fresh);
}

bool    stop_eating(t_data *data)
{
    return (boolean_get(&data->data_lock, &data->end));
}
