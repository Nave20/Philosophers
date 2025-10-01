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

int	phil_eat(t_phil *phil)
{
	if (phil->forks[0] > phil->forks[1])
		return (case_one(phil));
	else
		return (case_two(phil));
}

void	phil_sleep(t_phil *phil)
{
	print_mutex(SLEEP, *phil);
	ft_sleep(phil->data->time_to_sleep);
	if (get_status(phil->data) == ALIVE)
	{
		print_mutex(THINK, *phil);
		if (phil->id % 2 != 0 && phil->data->time_to_sleep
			< phil->data->time_to_eat)
			ft_sleep(phil->data->time_to_eat
				- phil->data->time_to_sleep + 20);
		else
			usleep(200);
	}
}

static void	phil_rout_bis(t_phil *phil)
{
	while (get_status(phil->data) == ALIVE)
	{
		handle_mutex(&phil->meal_mutex, LOCK);
		if (phil->data->must_eat > 0
			&& phil->meal_eaten >= phil->data->must_eat)
		{
			handle_mutex(&phil->meal_mutex, UNLOCK);
			break ;
		}
		handle_mutex(&phil->meal_mutex, UNLOCK);
		if (phil_eat(phil) && get_status(phil->data) == ALIVE)
		{
			phil_sleep(phil);
		}
	}
}

void	*phil_routine(void *args)
{
	t_phil	*phil;

	phil = args;
	while (!get_start(phil->data))
		usleep(200);
	handle_mutex(&phil->data->monitor, LOCK);
	if (phil->data->valid_simulation != phil->data->phil_nbr)
	{
		handle_mutex(&phil->data->monitor, UNLOCK);
		return (NULL);
	}
	phil->last_meal = get_time() - phil->data->start_time;
	handle_mutex(&phil->data->monitor, UNLOCK);
	if (phil->data->phil_nbr == 1)
		return (phil_alone(phil));
	print_mutex(THINK, *phil);
	if (phil->id % 2)
	{
		print_mutex(THINK, *phil);
		usleep(phil->data->time_to_eat * 100);
	}
	phil_rout_bis(phil);
	return (NULL);
}
