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

void	update_phil(t_phil *phil)
{
	long	time;

	time = get_time();
	handle_mutex(&phil->meal_mutex, LOCK);
	phil->meal_eaten++;
	phil->last_meal = time - phil->data->start_time;
	handle_mutex(&phil->meal_mutex, UNLOCK);
}

int	phil_eat(t_phil *phil)
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

void	*phil_alone(t_phil *phil)
{
	handle_mutex(phil->forks[0], LOCK);
	print_mutex(FORK, *phil);
	ft_sleep(phil->data->time_to_die);
	print_mutex(DIED, *phil);
	handle_mutex(&phil->data->monitor, LOCK);
	phil->data->schrodinger = DEAD;
	handle_mutex(&phil->data->monitor, UNLOCK);
	return (NULL);
}

void	*phil_routine(void *args)
{
	t_phil	*phil;

	phil = args;
	if (phil->data->phil_nbr == 1)
		return (phil_alone(phil));
	if (phil->id == phil->data->phil_nbr - 1)
		print_mutex(THINK, *phil);
	if (phil->id % 2)
	{
		print_mutex(THINK, *phil);
		usleep(phil->data->time_to_eat * 100);
	}
	handle_mutex(&phil->meal_mutex, LOCK);
	phil->last_meal = get_time() - phil->data->start_time;
	handle_mutex(&phil->meal_mutex, UNLOCK);
	phil_rout_bis(phil);
	return (NULL);
}
