/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:02:47 by salsoysa          #+#    #+#             */
/*   Updated: 2025/07/28 22:47:28 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

long get_time(t_time time)
{
	struct timeval t;

	if (gettimeofday(&t, NULL))
		return(ft_print_error("Failed to gettimeofday"));
	if (time == S)
		return (t.tv_sec + (t.tv_usec / 1000000));
	else if (time == MILLI_S)
		return ((t.tv_sec * 1000) / (t.tv_usec / 1000));
	else if ( time == MICRO_S)
		return ((t.tv_sec * 1000000) / t.tv_usec);
	else
		return(ft_print_error("Failed to get correct time input"));
}

int ft_print_error(char *str)
{
    printf("Error: %s\n", str);
    return (-1);
}

int mutex_foo(pthread_mutex_t *mutex, t_code type)
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

int thread_foo(pthread_t *thread, void *(*foo)(void *), void *data, t_code type)
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
