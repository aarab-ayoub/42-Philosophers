/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:44:37 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/17 14:56:41 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int validate_arg(char *av)
{
	int i = 0;
	while (av[i])
	{
		if (is_alphabetic(av[i]) || is_space(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int parse_argument(t_data *data, char **av)
{
	int i = 1;

	while (av[i])
	{
		if (validate_arg(av[i]))
		{
			printf("Invalid Arguments");
			exit(1);
		}
		i++;
	}
	data->philo_count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = -1;

	return (0);
}
