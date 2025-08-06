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
	long	sleep_time;

	// Pour Valgrind : éviter les boucles avec get_time()
	// Dormir en gros blocs pour réduire les appels système
	sleep_time = useconds;
	
	// Dormir par blocs de maximum 5ms pour permettre l'interruption
	while (sleep_time > 0 && !stop_eating(data))
	{
		if (sleep_time > 5000)  // Plus de 5ms
		{
			usleep(5000);
			sleep_time -= 5000;
		}
		else
		{
			usleep(sleep_time);
			break;
		}
	}
}
