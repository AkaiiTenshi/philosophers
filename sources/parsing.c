/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:14:34 by salsoysa          #+#    #+#             */
/*   Updated: 2025/07/29 19:29:26 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static inline bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*args_check(const char *str)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (NULL);
	if (!ft_isdigit(str[i]))
		return (NULL);
	while (str[i] && ft_isdigit(str[i]))
	{
		size++;
		i++;
	}
	if (size > 10)
		return (NULL);
	return (str + (i - size));
}

static long	ft_atol(char const *str)
{
	long	nbr;
	int		i;

	nbr = 0;
	i = 0;
	str = args_check(str);
	if (!str)
		return (ft_print_error("Found an error during parsing"));
	while (str[i] && str[i] == '0')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	if (nbr > INT_MAX)
		return (ft_print_error("One of the arguments is higher thant INT MAX"));
	return (nbr);
}

int	parse(t_data *data, char **av)
{
	data->nu_philo = ft_atol(av[1]);
	data->ttd = ft_atol(av[2]) * 1000;
	data->tte = ft_atol(av[3]) * 1000;
	data->tts = ft_atol(av[4]) * 1000;
	if (data->nu_philo == -1 || data->ttd == -1 || data->tte == -1
		|| data->tts == -1)
		return (-1);
	if (data->ttd < 60000 || data->tte < 60000 || data->tts < 60000)
		return (ft_print_error("Time limits must be higher than 60ms"));
	if (av[5])
		data->max_meals = ft_atol(av[5]);
	else
		data->max_meals = -1;
	return (0);
}
