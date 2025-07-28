/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:35:24 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/28 00:34:04 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				philosopher_routine, &data->philos[i]))
		{
			printf("Error: Failed to create thread %d\n", i);
			data->all_died = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_monitor_thread(t_data *data, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, monitor_routine, data))
	{
		printf("Error: Failed to create monitor thread\n");
		data->all_died = 1;
		return (1);
	}
	return (0);
}

void	join_all_threads(t_data *data, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor;

	if (ac != 5 && ac != 6)
	{
		printf("Error\n");
		return (1);
	}
	if (parse_argument(&data, av))
	{
		printf("Error invalid arguments\n");
		return (1);
	}
	if (init_data(&data))
	{
		printf("Error Initialization failed\n");
		return (1);
	}
	if (create_philosopher_threads(&data) || create_monitor_thread(&data,
			&monitor))
		return (1);
	join_all_threads(&data, monitor);
	cleanup_data(&data);
	printf("Cleanup complete!\n");
	return (0);
}
