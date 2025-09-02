/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:19:25 by vpirotti          #+#    #+#             */
/*   Updated: 2025/09/02 13:19:25 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	print_mutex(const char *str, t_phil phil)
{
	int		status;
	long	time;

	status = get_status(phil.data);
	if (status == ALIVE)
	{
		handle_mutex(&phil.data->print, LOCK);
		status = get_status(phil.data);
		if (status == ALIVE)
		{
			time = get_time() - phil.data->start_time;
			printf("%ld %d %s", time, phil.id, str);
		}
		handle_mutex(&phil.data->print, UNLOCK);
	}
}
