/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:10:22 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/28 00:46:57 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_data *data, int i)
{
	size_t	current_time;
	size_t	last_meal;
	size_t	mealing_time;

	pthread_mutex_lock(&data->eat_count_mutex);
	last_meal = data->philos[i].last_meal_time;
	current_time = get_current_time_ms();
	pthread_mutex_unlock(&data->eat_count_mutex);
	mealing_time = current_time - last_meal;
	if (mealing_time > (size_t)data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->all_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
		safe_print(data, data->philos[i].id, "died");
		return (1);
	}
	return (0);
}

int	check_all_eaten(t_data *data)
{
	int	finish;
	int	i;

	if (data->must_eat_count <= 0)
		return (0);
	finish = 1;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->eat_count_mutex);
		if (data->philos[i].meals_eaten < data->must_eat_count)
			finish = 0;
		pthread_mutex_unlock(&data->eat_count_mutex);
		if (!finish)
			break ;
		i++;
	}
	if (finish)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->all_ate = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!is_over(data))
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
			i++;
		}
		if (check_all_eaten(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
