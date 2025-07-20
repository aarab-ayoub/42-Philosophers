/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:34:06 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/19 18:46:28 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

// Forward declaration
typedef struct s_data t_data;

typedef struct s_philo
{
	int	id;
	int	l_fork_id;
	int r_fork_id;
	int meals_eaten;
	
	size_t last_meal_time;

	pthread_t thread_id;

	t_data *data;
	
} t_philo ;

typedef struct s_data
{
	int philo_count;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat_count; //optional
	
	int all_ate;
	int all_died;
	
	size_t start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
	pthread_mutex_t death_mutex;
	pthread_mutex_t eat_count_mutex;
	
	t_philo *philos;
} t_data ;

int parse_argument(t_data *data, char **av);
int init_data(t_data *data);
void cleanup_data(t_data *data);
int is_alphabetic(char c);
int ft_atoi(const char *str);
int is_space(char c);
#endif