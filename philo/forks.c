/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:00:00 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/28 01:00:00 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->l_fork_id]);
	safe_print(philo->data, philo->id, "has taken a fork");
	usleep(philo->data->time_to_die * 1000 + 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork_id]);
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (philo->data->philo_count == 1)
		return (handle_single_philo(philo));
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->l_fork_id]);
		safe_print(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->r_fork_id]);
		safe_print(philo->data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->r_fork_id]);
		safe_print(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->l_fork_id]);
		safe_print(philo->data, philo->id, "has taken a fork");
	}
	return (0);
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork_id]);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork_id]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork_id]);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork_id]);
	}
}
