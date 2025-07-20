/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:35:24 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/19 18:46:28 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data data;
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
	
	printf("✅ Initialization successful!\n");
	printf("📊 Philosophers: %d\n", data.philo_count);
	printf("⏰ Start time: %zu ms\n", data.start_time);
	printf("🍴 Forks allocated: %d\n", data.philo_count);
	printf("🧠 Philosophers allocated: %d\n", data.philo_count);
	
	// Test cleanup
	printf("🧹 Cleaning up...\n");
	cleanup_data(&data);
	printf("✨ Cleanup complete!\n");
	
	return (0);
}
