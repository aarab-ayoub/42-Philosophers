/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:49:22 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/19 19:02:23 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data)
{
	if (!data)
		return (1);
	
	data->all_ate = 0;
	data->all_died = 0;
	
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos) 
	{
		free(data->forks);
		return (1);
	}
	int i = 0;
	while (i < data->philo_count) {
		if (pthread_mutex_init(&data->forks[i], NULL) != 0) {
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			free(data->philos);
			return (1);
		}
		i++;
	}
	
	// Initialize control mutexes
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0 ||
		pthread_mutex_init(&data->death_mutex, NULL) != 0 ||
		pthread_mutex_init(&data->eat_count_mutex, NULL) != 0) {
		// Clean up fork mutexes
		i = 0;
		while (i < data->philo_count) {
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		free(data->philos);
		return (1);
	}
	
	// Set start time
	struct timeval tv;
	gettimeofday(&tv, NULL);
	data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	
	// Initialize each philosopher
	i = 0;
	while (i < data->philo_count) {
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		
		// Assign fork IDs (circular arrangement)
		data->philos[i].l_fork_id = i;
		data->philos[i].r_fork_id = (i + 1) % data->philo_count;
		
		i++;
	}
	
	return (0);
}