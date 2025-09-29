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

void	update_phil(t_phil *phil)
{
	long	time;

	time = get_time();
	handle_mutex(&phil->meal_mutex, LOCK);
	handle_mutex(&phil->data->monitor, LOCK);
	phil->meal_eaten++;
	phil->last_meal = time - phil->data->start_time;
	handle_mutex(&phil->data->monitor, UNLOCK);
	handle_mutex(&phil->meal_mutex, UNLOCK);
}

int	phil_died(t_data *data, const int i)
{
	long	time;

	handle_mutex(&data->monitor, LOCK);
	time = get_time() - data->start_time;
	if (time - data->phil[i]->last_meal >= data->time_to_die)
	{
		print_mutex_die(DIED, *data->phil[i]);
		data->schrodinger = DEAD;
		handle_mutex(&data->monitor, UNLOCK);
		return (1);
	}
	handle_mutex(&data->monitor, UNLOCK);
	return (0);
}

int	phil_full(t_data *data, const int i)
{
	handle_mutex(&data->monitor, LOCK);
	if (data->must_eat <= data->phil[i]->meal_eaten)
	{
		if (data->must_eat > 0)
		{
			handle_mutex(&data->monitor, UNLOCK);
			return (1);
		}
		else
		{
			handle_mutex(&data->monitor, UNLOCK);
			return (0);
		}
	}
	handle_mutex(&data->monitor, UNLOCK);
	return (0);
}

void	monitor_bis(t_data *data, int *phil_nbr_full)
{
	int	i;

	i = 0;
	while (i < data->phil_nbr && get_status(data) == ALIVE)
	{
		handle_mutex(&data->print, LOCK);
		if (phil_died(data, i))
		{
			handle_mutex(&data->print, UNLOCK);
			break ;
		}
		*phil_nbr_full += phil_full(data, i);
		i++;
		handle_mutex(&data->print, UNLOCK);
	}
}

void	*monitor_rout(void *arg)
{
	t_data	*data;
	int		phil_nbr_full;

	data = arg;
	phil_nbr_full = 0;
	usleep(1000);
	while (get_status(data) == ALIVE)
	{
		if (phil_nbr_full >= data->phil_nbr)
			break ;
		monitor_bis(data, &phil_nbr_full);
		usleep(500);
	}
	return (NULL);
}
