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
