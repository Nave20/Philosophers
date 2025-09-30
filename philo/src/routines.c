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

int	case_one(t_phil *phil)
{
	handle_mutex(phil->forks[1], LOCK);
	if (get_status(phil->data) != ALIVE)
	{
		handle_mutex(phil->forks[1], UNLOCK);
		return (1);
	}
	print_mutex(FORK, *phil);
	handle_mutex(phil->forks[0], LOCK);
	if (get_status(phil->data) != ALIVE)
	{
		handle_mutex(phil->forks[0], UNLOCK);
		handle_mutex(phil->forks[1], UNLOCK);
		return (1);
	}
	print_mutex(FORK, *phil);
	print_mutex(EAT, *phil);
	ft_sleep(phil->data->time_to_eat);
	handle_mutex(phil->forks[0], UNLOCK);
	handle_mutex(phil->forks[1], UNLOCK);
	update_phil(phil);
	return (1);
}

int	case_two(t_phil *phil)
{
	handle_mutex(phil->forks[0], LOCK);
	if (get_status(phil->data) != ALIVE)
	{
		handle_mutex(phil->forks[0], UNLOCK);
		return (1);
	}
	print_mutex(FORK, *phil);
	handle_mutex(phil->forks[1], LOCK);
	if (get_status(phil->data) != ALIVE)
	{
		handle_mutex(phil->forks[1], UNLOCK);
		handle_mutex(phil->forks[0], UNLOCK);
		return (1);
	}
	print_mutex(FORK, *phil);
	print_mutex(EAT, *phil);
	ft_sleep(phil->data->time_to_eat);
	handle_mutex(phil->forks[1], UNLOCK);
	handle_mutex(phil->forks[0], UNLOCK);
	update_phil(phil);
	return (1);
}

int	phil_eat(t_phil *phil)
{
	if (phil->forks[0] > phil->forks[1])
		return (case_one(phil));
	else
		return (case_two(phil));
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
			print_mutex(SLEEP, *phil);
			ft_sleep(phil->data->time_to_sleep);
			if (get_status(phil->data) == ALIVE)
			{
				print_mutex(THINK, *phil);
				usleep(200);
			}
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
	if (phil->id == phil->data->phil_nbr - 1)
		print_mutex(THINK, *phil);
	if (phil->id % 2)
	{
		print_mutex(THINK, *phil);
		usleep(phil->data->time_to_eat * 100);
	}
	phil_rout_bis(phil);
	return (NULL);
}
