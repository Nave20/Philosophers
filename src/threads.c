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

int	thread_launch(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data->phil_nbr)
	{
		if (pthread_create(&all->phil[i]->thread, NULL, phil_routine,
			all->phil[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < all->data->phil_nbr)
	{
		if (pthread_join(all->phil[i]->thread, NULL))
			return (1);
		i++;
	}
	return (0);
}
