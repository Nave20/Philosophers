/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:31:29 by vpirotti          #+#    #+#             */
/*   Updated: 2025/09/03 12:31:29 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	phil_died(t_data *data, const int i)
{
	long	time;

	time = get_time() - data->start_time;
	handle_mutex(&data->phil[i]->meal_mutex, LOCK);
	if (time - data->phil[i]->last_meal >= data->time_to_die)
	{
		handle_mutex(&data->phil[i]->meal_mutex, UNLOCK);
		print_mutex(DIED, *data->phil[i]);
		handle_mutex(&data->monitor, LOCK);
		data->schrodinger = DEAD;
		handle_mutex(&data->monitor, UNLOCK);
		return (1);
	}
	handle_mutex(&data->phil[i]->meal_mutex, UNLOCK);
	return (0);
}

int	phil_full(t_data *data, const int i)
{
	handle_mutex(&data->phil[i]->meal_mutex, LOCK);
	if (data->must_eat <= data->phil[i]->meal_eaten)
	{
		handle_mutex(&data->phil[i]->meal_mutex, UNLOCK);
		return (1);
	}
	handle_mutex(&data->phil[i]->meal_mutex, UNLOCK);
	return (0);
}

void	*monitor_rout(void *arg)
{
	t_data	*data;
	int		phil_nbr_full;
	int		i;

	data = arg;
	phil_nbr_full = 0;
	usleep(1000);
	while (get_status(data) == ALIVE)
	{
		i = 0;
		if (phil_nbr_full >= data->phil_nbr)
			break ;
		while (i < data->phil_nbr && get_status(data) == ALIVE)
		{
			if (phil_died(data, i))
				break ;
			phil_nbr_full += phil_full(data, i);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
