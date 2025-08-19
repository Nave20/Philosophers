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
	return (1);
}

int	inv_args_bis(t_all *all, const char *str)
{
	ft_putstr_fd(RED"invalid argument : "YELLOW BOLD, 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(RESET RED", acceptable arguments are"
						" in range of INT."RESET, 2);
	all->error = 1;
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