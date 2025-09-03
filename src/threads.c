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

int	thread_launch(t_data *data)
{
	int			i;
	pthread_t	big_brother;

	if (pthread_create(&big_brother, NULL, monitor_rout, data))
		return (1);
	i = 0;
	data->start_time = get_time();
	while (i < data->phil_nbr)
	{
		if (pthread_create(&data->phil[i]->thread, NULL, phil_routine,
				data->phil[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < data->phil_nbr)
	{
		if (pthread_join(data->phil[i]->thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(big_brother, NULL))
		return (1);
	return (0);
}
