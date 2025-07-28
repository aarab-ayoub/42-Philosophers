/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:00:00 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/28 01:00:00 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	safe_print(t_data *data, int philo_id, char *action)
{
	size_t	timestamp;

	pthread_mutex_lock(&data->print_mutex);
	timestamp = get_current_time_ms() - data->start_time;
	printf("Time %zums Philosopher %d %s\n", timestamp, philo_id + 1, action);
	pthread_mutex_unlock(&data->print_mutex);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_over(philo->data))
	{
		think(philo);
		if (take_forks(philo) == 0)
		{
			eat(philo);
			drop_forks(philo);
			sleep_philo(philo);
		}
	}
	return (NULL);
}
