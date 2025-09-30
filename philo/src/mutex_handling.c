/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:45:32 by vpirotti          #+#    #+#             */
/*   Updated: 2025/09/02 12:45:32 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	get_status(t_data *data)
{
	int	res;

	handle_mutex(&data->monitor, LOCK);
	res = data->schrodinger;
	handle_mutex(&data->monitor, UNLOCK);
	return (res);
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
			usleep(10);
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
			usleep(10);
			if (get_status(data) != ALIVE)
				return (1);
		}
		handle_mutex(&fork->fork_mutex, LOCK);
		fork->fork_lock = UNLOCK;
		handle_mutex(&fork->fork_mutex, UNLOCK);
	}
	return (0);
}

int	handle_mutex(pthread_mutex_t *mutex, t_lock status)
{
	if (status == LOCK)
	{
		if (pthread_mutex_lock(mutex))
			return (1);
	}
	else if (status == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex))
			return (1);
	}
	return (0);
}
