/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:49:22 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/28 00:33:56 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_memory(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
	{
		free(data->forks);
		return (1);
	}
	return (0);
}

int	init_fork_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			free(data->philos);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	if (init_fork_mutexes(data))
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0
		|| pthread_mutex_init(&data->death_mutex, NULL) != 0
		|| pthread_mutex_init(&data->eat_count_mutex, NULL) != 0)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		free(data->philos);
		return (1);
	}
	return (0);
}

void	init_timing_and_philos(t_data *data)
{
	struct timeval	tv;
	int				i;

	gettimeofday(&tv, NULL);
	data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		data->philos[i].l_fork_id = i;
		data->philos[i].r_fork_id = (i + 1) % data->philo_count;
		i++;
	}
}

int	init_data(t_data *data)
{
	if (!data)
		return (1);
	data->all_ate = 0;
	data->all_died = 0;
	if (allocate_memory(data))
		return (1);
	if (init_mutexes(data))
		return (1);
	init_timing_and_philos(data);
	return (0);
}
