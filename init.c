/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:49:22 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/16 17:36:35 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data)
{
	if (!data)
		return (1);
	
	data->all_ate = 0;
	data->all_died = 0;
	
	// TODO: Initialize mutexes, allocate memory for forks and philos
	// TODO: Set start_time
	// TODO: Initialize each philosopher
	
	return (0);
}