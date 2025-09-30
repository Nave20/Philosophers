/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_alone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:03:41 by vpirotti          #+#    #+#             */
/*   Updated: 2025/09/29 15:03:53 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*phil_alone(t_phil *phil)
{
	handle_fork_mutex(phil->forks[0], LOCK, phil->data);
	print_mutex(FORK, *phil);
	ft_sleep(phil->data->time_to_die);
	print_mutex(DIED, *phil);
	handle_mutex(&phil->data->monitor, LOCK);
	phil->data->schrodinger = DEAD;
	handle_mutex(&phil->data->monitor, UNLOCK);
	return (NULL);
}
