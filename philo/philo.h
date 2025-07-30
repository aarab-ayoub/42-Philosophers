/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaarab <ayaarab@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:34:06 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/28 00:27:19 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					l_fork_id;
	int					r_fork_id;
	int					meals_eaten;

	size_t				last_meal_time;

	pthread_t			thread_id;

	t_data				*data;

}						t_philo;

typedef struct s_data
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;

	int					all_ate;
	int					all_died;

	size_t				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		eat_count_mutex;

	t_philo				*philos;
}						t_data;

int						parse_argument(t_data *data, char **av);
int						init_data(t_data *data);
int						allocate_memory(t_data *data);
int						init_fork_mutexes(t_data *data);
int						init_mutexes(t_data *data);
void					init_timing_and_philos(t_data *data);
void					cleanup_data(t_data *data);
int						is_alphabetic(char c);
long					ft_atol(const char *str);
int						is_space(char c);
void					*philosopher_routine(void *arg);
size_t					get_current_time_ms(void);
void					safe_print(t_data *data, int philo_id, char *action);
int						is_over(t_data *data);
void					*monitor_routine(void *arg);
int						check_philosopher_death(t_data *data, int i);
int						check_all_eaten(t_data *data);
int						take_forks(t_philo *philo);
void					drop_forks(t_philo *philo);
int						handle_single_philo(t_philo *philo);
void					eat(t_philo *philo);
void					sleep_philo(t_philo *philo);
void					think(t_philo *philo);
int						create_philosopher_threads(t_data *data);
int						create_monitor_thread(t_data *data, pthread_t *monitor);
void					join_all_threads(t_data *data, pthread_t monitor);

#endif