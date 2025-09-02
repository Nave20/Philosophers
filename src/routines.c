/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:41:41 by vpirotti          #+#    #+#             */
/*   Updated: 2025/09/02 12:41:41 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

// void	phil_eat(t_phil *phil)
// {
// 	if ()
// }

static void	phil_rout_bis(t_phil *phil)
{
	while (get_status(phil->data) == ALIVE)
	{
		handle_mutex(&phil->meal_mutex, LOCK);
		if (phil->data->must_eat > 0 && phil->meal_eaten >= phil->data->must_eat)
		{
			handle_mutex(&phil->meal_mutex, UNLOCK);
			break ;
		}
	}
}

void	*phil_routine(void *args)
{
	t_phil	*phil;

	phil = args;
	if (phil->id % 2)
		usleep(phil->data->time_to_eat * 100);
	handle_mutex(&phil->meal_mutex, LOCK);
	phil->last_meal = get_time();
	handle_mutex(&phil->meal_mutex, UNLOCK);
	print_mutex("test\n", *phil);
	phil_rout_bis(phil);
	return (NULL);
}
