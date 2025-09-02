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

void	free_all(t_all *all)
{
	free_phil(all);
	if (all->data)
		free(all->data);
	free(all);
}

void	free_phil(t_all	*all)
{
	int	i;

	i = 0;
	while (i < all->data->phil_nbr)
	{
		pthread_mutex_destroy(&all->phil[i]->meal_mutex);
		free(all->phil[i]);
		i++;
	}
	free(all->phil);
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
}