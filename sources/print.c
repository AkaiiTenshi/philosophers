/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:47:11 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/10 14:36:26 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printfoo(t_dinner state, t_philo *philo)
{
	long	t;

	t = get_time(MILLI_S) - philo->data->start;
	if (philo->done)
		return ;
	mutex_foo(&philo->data->print_lock, LOCK);
	if ((state == TOOK_FORK1 || state == TOOK_FORK2)
		&& !stop_eating(philo->data))
		printf(CYAN"%-6ld""%d has taken a fork\n"WHITE, t, philo->id);
	else if ((state == SLEEPING) && !stop_eating(philo->data))
		printf(GREEN"%-6ld""%d is sleeping\n"WHITE, t, philo->id);
	else if ((state == EATING) && !stop_eating(philo->data))
		printf(MAGENTA"%-6ld" "%d is eating\n"WHITE, t, philo->id);
	else if (state == DIED && !stop_eating(philo->data))
		printf(RED"%-6ld" "%d died\n"WHITE, t, philo->id);
	else if ((state == THINKING) && !stop_eating(philo->data))
		printf(YELLOW"%-6ld" "%d is thinking\n"WHITE, t, philo->id);
	mutex_foo(&philo->data->print_lock, UNLOCK);
}
