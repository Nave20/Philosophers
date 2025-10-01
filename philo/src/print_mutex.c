/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:19:25 by vpirotti          #+#    #+#             */
/*   Updated: 2025/10/01 14:59:15 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	print_mutex(const char *str, t_phil phil)
{
	long	time;

	handle_mutex(&phil.data->print, LOCK);
	if (get_status(phil.data) == ALIVE)
	{
		handle_mutex(&phil.data->monitor, LOCK);
		time = get_time() - phil.data->start_time;
		handle_mutex(&phil.data->monitor, UNLOCK);
		printf("\033[37m%ld "RESET BOLD"%d"RESET "%s",
			time, phil.id + 1, str);
	}
	handle_mutex(&phil.data->print, UNLOCK);
}

void	print_mutex_die(const char *str, t_phil phil)
{
	long	time;

	if (phil.data->schrodinger == ALIVE)
	{
		time = get_time() - phil.data->start_time;
		printf("\033[37m%ld "RESET BOLD"%d"RESET "%s",
			time, phil.id + 1, str);
	}
}
