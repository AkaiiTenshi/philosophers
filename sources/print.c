/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:47:11 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/06 23:06:23 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printfoo(t_dinner state, t_philo *philo)
{
	long	t;

	t = get_time(MILLI_S) - philo->data->start;
	if (boolean_get(&philo->philo_lock, &philo->done))
		return ;
	mutex_foo(&philo->data->print_lock, LOCK);
	if ((state == TOOK_FORK1 || state == TOOK_FORK2)
		&& !stop_eating(philo->data))
		printf("%-6ld""%d has taken a fork\n", t, philo->id);
	else if ((state == SLEEPING) && !stop_eating(philo->data))
		printf("%-6ld""%d is sleeping\n", t, philo->id);
	else if ((state == EATING) && !stop_eating(philo->data))
		printf("%-6ld" "%d is eating\n", t, philo->id);
	else if (state == DIED)
		printf("%-6ld" "%d died\n", t, philo->id);
	else if ((state == THINKING) && !stop_eating(philo->data))
		printf("%-10ld" "%d is thinking\n", t, philo->id);
	mutex_foo(&philo->data->print_lock, UNLOCK);
}
