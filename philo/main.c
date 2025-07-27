/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:35:24 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/27 15:16:19 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data data;
	pthread_t monitor;
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
	int i = 0;
	while (i < data.philo_count)
	{
		if (pthread_create(&data.philos[i].thread_id, NULL, philosopher_routine, &data.philos[i])) {
			printf("Error: Failed to create thread %d\n", i);
			data.all_died = 1;
			break;
		}
		i++;
	}
	if (pthread_create(&monitor , NULL , monitor_routine , &data))
	{
		printf("Error: Failed to create monitor thread %d\n", i);
		data.all_died =1;
	}
	
	pthread_join(monitor, NULL);
	
		i = 0;
	while (i < data.philo_count) {
		pthread_join(data.philos[i].thread_id, NULL);
		i++;
	}
	
	cleanup_data(&data);
	printf("Cleanup complete!\n");
	
	return (0);
}
