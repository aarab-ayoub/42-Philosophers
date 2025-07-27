/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:00:00 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/27 14:47:04 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_current_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void safe_print(t_data *data, int philo_id, char *action)
{
    pthread_mutex_lock(&data->print_mutex);
    
    size_t timestamp = get_current_time_ms() - data->start_time;
    printf("Time %zums Philosopher %d %s\n", timestamp, philo_id + 1, action);
    
    pthread_mutex_unlock(&data->print_mutex);
}

int take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0) {
        pthread_mutex_lock(&philo->data->forks[philo->l_fork_id]);
        safe_print(philo->data, philo->id, "has taken a fork");
        
        pthread_mutex_lock(&philo->data->forks[philo->r_fork_id]);
        safe_print(philo->data, philo->id, "has taken a fork");
    } else {
        pthread_mutex_lock(&philo->data->forks[philo->r_fork_id]);
        safe_print(philo->data, philo->id, "has taken a fork");
        
        pthread_mutex_lock(&philo->data->forks[philo->l_fork_id]);
        safe_print(philo->data, philo->id, "has taken a fork");
    }
    return (0);
}

void drop_forks(t_philo *philo)
{
    if (philo->id % 2 == 0) {
        pthread_mutex_unlock(&philo->data->forks[philo->r_fork_id]);
        pthread_mutex_unlock(&philo->data->forks[philo->l_fork_id]);
    } else {
        pthread_mutex_unlock(&philo->data->forks[philo->l_fork_id]);
        pthread_mutex_unlock(&philo->data->forks[philo->r_fork_id]);
    }
}

void eat(t_philo *philo)
{
    safe_print(philo->data, philo->id, "is eating");
    
    pthread_mutex_lock(&philo->data->eat_count_mutex);
    philo->last_meal_time = get_current_time_ms();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->eat_count_mutex);
    
    usleep(philo->data->time_to_eat * 1000);
}


void sleep_philo(t_philo *philo)
{
    safe_print(philo->data, philo->id, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
}

void think(t_philo *philo)
{
    safe_print(philo->data, philo->id, "is thinking");
}

int is_over(t_data *data)
{
    int result;
    result = 0;
    pthread_mutex_lock(&data->death_mutex);
    if (data->all_died || data->all_ate)
        result = 1;
    pthread_mutex_unlock(&data->death_mutex);
    return (result);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    if (philo->id % 2 == 0)
        usleep(1000);
    
    while (!is_over(philo->data)) {
        think(philo);
        
        take_forks(philo);
        eat(philo);
        drop_forks(philo);
        
        sleep_philo(philo);
    }
    
    return (NULL);
}

