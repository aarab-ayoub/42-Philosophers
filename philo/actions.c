/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:00:00 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/28 01:00:00 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	nap(t_data *data, int time)
{
	size_t	current;

	current = get_current_time_ms();
	while (!is_over(data))
	{
		if (get_current_time_ms() - current >= (size_t)time)
			break ;
		usleep(100);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_count_mutex);
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->eat_count_mutex);
	safe_print(philo->data, philo->id, "is eating");
	nap(philo->data, philo->data->time_to_eat);
}

void	sleep_philo(t_philo *philo)
{
	safe_print(philo->data, philo->id, "is sleeping");
	nap(philo->data, philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	safe_print(philo->data, philo->id, "is thinking");
}

int	is_over(t_data *data)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&data->death_mutex);
	if (data->all_died || data->all_ate)
		result = 1;
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}
