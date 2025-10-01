/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:37:45 by vpirotti          #+#    #+#             */
/*   Updated: 2025/09/02 12:37:45 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	time_set(t_data *data)
{
	handle_mutex(&data->monitor, LOCK);
	data->start_time = get_time();
	data->valid_simulation = 0;
	data->start = 0;
	handle_mutex(&data->monitor, UNLOCK);
}

int	get_start(t_data *data)
{
	handle_mutex(&data->monitor, LOCK);
	if (data->start)
	{
		handle_mutex(&data->monitor, UNLOCK);
		return (1);
	}
	handle_mutex(&data->monitor, UNLOCK);
	return (0);
}

int	thread_error(t_data *data, int i, pthread_t big_b)
{
	handle_mutex(&data->monitor, LOCK);
	data->start = 1;
	handle_mutex(&data->monitor, UNLOCK);
	while (i >= 0)
	{
		pthread_join(data->phil[i]->thread, NULL);
		i--;
	}
	pthread_join(big_b, NULL);
	return (1);
}

int	thread_creation(t_data *data, int i, pthread_t big_brother)
{
	if (pthread_create(&data->phil[i]->thread, NULL, phil_routine,
			data->phil[i]) == 0)
	{
		handle_mutex(&data->monitor, LOCK);
		data->valid_simulation++;
		handle_mutex(&data->monitor, UNLOCK);
	}
	else
		return (thread_error(data, i - 1, big_brother));
	return (0);
}

int	thread_launch(t_data *data)
{
	int			i;
	pthread_t	big_brother;

	time_set(data);
	if (pthread_create(&big_brother, NULL, monitor_rout, data))
		return (1);
	i = 0;
	while (i < data->phil_nbr)
	{
		if (thread_creation(data, i, big_brother))
			return (1);
		i++;
	}
	i--;
	handle_mutex(&data->monitor, LOCK);
	data->start = 1;
	data->start_time = get_time();
	handle_mutex(&data->monitor, UNLOCK);
	while (i >= 0)
	{
		pthread_join(data->phil[i]->thread, NULL);
		i--;
	}
	pthread_join(big_brother, NULL);
	return (0);
}
