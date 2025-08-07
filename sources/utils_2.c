/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:40:03 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/07 14:55:06 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	better_usleep(long useconds, t_data *data)
{
	long	sleep_time;

	sleep_time = useconds;
	while (sleep_time > 0 && !stop_eating(data))
	{
		if (sleep_time > 5000)
		{
			usleep(5000);
			sleep_time -= 5000;
		}
		else
		{
			usleep(sleep_time);
			break ;
		}
	}
}
