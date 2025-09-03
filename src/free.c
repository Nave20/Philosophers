/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:39:54 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/21 13:39:54 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	free_all(t_data *data)
{
	free_phil(data);
	free_data(data);
	free(data);
}

void	free_phil(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phil_nbr)
	{
		pthread_mutex_destroy(&data->phil[i]->meal_mutex);
		free(data->phil[i]);
		i++;
	}
	free(data->phil);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->monitor);
	pthread_mutex_destroy(&data->print);
	while (i < data->phil_nbr)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		i++;
	}
	free(data->fork_mutex);
}

int	exit_init(t_data *data, int max)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->monitor);
	while (i < max)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		i++;
	}
	return (1);
}