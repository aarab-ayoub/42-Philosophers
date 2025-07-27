/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:10:22 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/27 15:25:42 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;
	while (!is_over(data))
	{
		i = 0;
		while (i < data->philo_count)
		{
			size_t current_time = get_current_time_ms();
			size_t mealing_time = current_time - data->philos[i].last_meal_time;
			if (mealing_time > (size_t)data->time_to_die)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->all_died = 1;
				pthread_mutex_unlock(&data->death_mutex);
				safe_print(data , data->philos[i].id , "died");
				return (NULL);
			}
			i++;
		}

		if (data->must_eat_count > 0)
		{
			int finish = 1;
			int i = 0;
			while (i < data->philo_count)
			{
				pthread_mutex_lock(&data->eat_count_mutex);
				if (data->philos[i].meals_eaten < data->must_eat_count)
                    finish = 0;
                pthread_mutex_unlock(&data->eat_count_mutex);
                if (!finish)
                    break;
                i++;
			}
			if (finish)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->all_ate = 1;
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}