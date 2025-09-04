/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:08:47 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/19 12:08:47 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	inv_args(void)
{
	ft_putendl_fd(RED"invalid number of arguments."RESET, 2);
	printf(RED"Usage : ./philo [number_of_philosophers] "
			"[time_to_die] [time_to_eat] [time_to_sleep]"
			" [# number_of_times_each_philosopher_must_eat]\n"RESET);
	return (1);
}

int	inv_args_bis(t_data *data, const char *str)
{
	ft_putstr_fd(RED"invalid argument : "YELLOW BOLD, 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(RESET RED", arguments must be"
		" in range of INT."RESET, 2);
	data->error = 1;
	return (0);
}

int	inv_args_third(const char *str)
{
	ft_putstr_fd(RED"invalid argument : "YELLOW BOLD, 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(RESET RED", arguments must "
		"only be positive numbers."RESET, 2);
	return (0);
}
