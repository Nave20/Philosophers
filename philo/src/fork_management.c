/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:34:28 by vpirotti          #+#    #+#             */
/*   Updated: 2025/10/02 14:26:14 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	case_one(t_phil *phil)
{
	handle_fork_mutex(phil->forks[1], LOCK, phil->data);
	if (get_status(phil->data) != ALIVE)
	{
		handle_fork_mutex(phil->forks[1], UNLOCK, phil->data);
		return (1);
	}
	print_mutex(FORK, *phil);
	handle_fork_mutex(phil->forks[0], LOCK, phil->data);
	if (get_status(phil->data) != ALIVE)
	{
		handle_fork_mutex(phil->forks[0], UNLOCK, phil->data);
		handle_fork_mutex(phil->forks[1], UNLOCK, phil->data);
		return (1);
	}
	print_mutex(FORK, *phil);
	print_mutex(EAT, *phil);
	update_phil(phil);
	ft_sleep(phil->data->time_to_eat);
	handle_fork_mutex(phil->forks[0], UNLOCK, phil->data);
	handle_fork_mutex(phil->forks[1], UNLOCK, phil->data);
	return (1);
}

int	get_fork_status(t_fork *fork)
{
	handle_mutex(&fork->fork_mutex, LOCK);
	if (fork->fork_lock == UNLOCK)
	{
		handle_mutex(&fork->fork_mutex, UNLOCK);
		return (0);
	}
	handle_mutex(&fork->fork_mutex, UNLOCK);
	return (1);
}

int	handle_fork_mutex(t_fork *fork, t_lock status, t_data *data)
{
	if (status == LOCK)
	{
		while (get_fork_status(fork))
		{
			usleep(400);
			if (get_status(data) != ALIVE)
				return (1);
		}
		handle_mutex(&fork->fork_mutex, LOCK);
		fork->fork_lock = LOCK;
		handle_mutex(&fork->fork_mutex, UNLOCK);
	}
	else if (status == UNLOCK)
	{
		while (!get_fork_status(fork))
		{
			usleep(400);
			if (get_status(data) != ALIVE)
				return (1);
		}
		handle_mutex(&fork->fork_mutex, LOCK);
		fork->fork_lock = UNLOCK;
		handle_mutex(&fork->fork_mutex, UNLOCK);
	}
	return (0);
}
