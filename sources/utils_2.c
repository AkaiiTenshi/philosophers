/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:40:03 by salsoysa          #+#    #+#             */
/*   Updated: 2025/07/28 22:47:31 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void better_usleep(long useconds, t_data *data)
{
	long	t;
	long	past_t;
	long	remaining;

	t = get_time(MICRO_S);
	while (get_time(MICRO_S) - t < useconds)
	{
		if (stop_eating(data))
			break ;
		past_t = get_time(MICRO_S) - t;
		remaining = useconds - past_t;
		if (remaining > 1000)
			usleep(500);
		else
		{
			while(get_time(MICRO_S) - t < useconds)
				;
		}
	}
}
