/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:44:37 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/28 00:16:23 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_positive_int(char *str, int min_val, int max_val)
{
	int		i;
	long	result;

	if (!str || *str == '\0')
		return (-1);
	i = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	if (str[i] == '\0')
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	result = ft_atol(str);
	if (result < min_val || result > max_val)
		return (-1);
	return ((int)result);
}

int	parse_argument(t_data *data, char **av)
{
	data->philo_count = validate_positive_int(av[1], 1, 200);
	if (data->philo_count == -1)
		return (1);
	data->time_to_die = validate_positive_int(av[2], 60, INT_MAX);
	data->time_to_eat = validate_positive_int(av[3], 60, INT_MAX);
	data->time_to_sleep = validate_positive_int(av[4], 60, INT_MAX);
	if (data->time_to_die == -1 || data->time_to_eat == -1
		|| data->time_to_sleep == -1)
		return (1);
	if (av[5])
	{
		data->must_eat_count = validate_positive_int(av[5], 1, INT_MAX);
		if (data->must_eat_count == -1)
			return (1);
	}
	else
		data->must_eat_count = -1;
	return (0);
}
