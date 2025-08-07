/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <salsoysa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:23:16 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/07 19:57:19 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo(char **av)
{
	t_data	data;

	if (parse(&data, av) == -1)
		return (-1);
	if (init(&data) == -1)
		return (-1);
	dinner_table(&data);
	clean(&data);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		return (philo(av));
	}
	else
	{
		printf("Correct input: ./philo nu_of_philos tt_die tt_eat tt_sleep");
		printf("[nu_of_times_each_philo_must_eat]\n");
		return (-1);
	}
}
