/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:44:37 by ayoub             #+#    #+#             */
/*   Updated: 2025/07/16 13:22:08 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int validate_arg(char *av)
{
	int i = 0;
	while (av[i])
	{
		if (is_alphabetic(av[i]) || is_space(av[i]))
		{
			printf("Invalide arguments\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse_argument(t_data *data , char **av)
{
	int i = 0;
	while (av[i])
	{
		if(!validate_arg(av[i]))
		
		
	}
	
}