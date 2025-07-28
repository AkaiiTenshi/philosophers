/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:02:47 by salsoysa          #+#    #+#             */
/*   Updated: 2025/07/28 14:14:25 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int ft_print_error(char *str)
{
    printf("Error: %s\n", str);
    return (-1);
}

int mutex_foo(pthread_mutex_t *mutex, t_enum type)
{
    if (type == DESTROY)
    {
        if (pthread_mutex_destroy(mutex))
            return (ft_print_error("Failed to destroy mutex"));
    }
    if (type == UNLOCK)
    {
        if (pthread_mutex_unlock(mutex))
            return (ft_print_error("Failed to unlock mutex"));
    }
    if (type == LOCK)
    {
        if (pthread_mutex_lock(mutex))
            return (ft_print_error("Failed to lock mutex"));
    }
    if (type == INIT)
    {
        if (pthread_mutex_init(mutex, NULL))
            return (ft_print_error("Failed to init mutex"));
    }
    return (0);
}

int thread_foo(pthread_t *thread, void *(*foo)(void *), void *data, t_enum type)
{
    if (type == CREATE)
    {
        if (pthread_create(thread, NULL, foo, data))
            return(ft_print_error("Failed to create thread"));
    }
    if (type == JOIN)
    {
        if (pthread_join(*thread, NULL))
            return(ft_print_error("Failed to join thread"));
    }
    if (type == DETACH)
    {
        if (pthread_detach(*thread))
            return(ft_print_error("Failed to detach thread"));
    }
    return (0);
}
