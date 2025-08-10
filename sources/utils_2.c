/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:40:03 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/10 08:14:40 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	better_usleep(long useconds, t_data *data)
{
    long    start;
    long    time_left;
    long    time;

    start = get_time(MICRO_S);
    while (get_time(MICRO_S) - start < useconds)
    {
        if (stop_eating(data))
            break ;
        time = get_time(MICRO_S) - start;
        time_left = useconds - time;
        if (time_left > 1000)
            usleep(time_left / 2);
        else
            while (get_time(MICRO_S) - start < useconds)
                ;
    }
}
