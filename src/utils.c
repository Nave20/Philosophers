/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:58:00 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/19 12:58:00 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	ft_sleep(int time)
{
	unsigned long	start_time;
	unsigned long	current_time;
	unsigned long	elapsed;

	start_time = get_time();
	while (1)
	{
		current_time = get_time();
		elapsed = current_time - start_time;
		if (elapsed >= (unsigned long)time)
			break ;
		if (time - elapsed > 10)
			usleep(1000);
		else
			usleep(100);
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	ft_putendl_fd(const char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (write(fd, &s[i], 1) == -1)
			return ;
		i++;
	}
	write(fd, "\n", 1);
}

int	ft_putstr_fd(const char *s, int fd)
{
	if (s == NULL)
		return ((int) write(fd, "(null)", 6));
	return ((int) write(fd, s, ft_strlen(s)));
}

void	print_data(t_data *data)
{
	printf(RED"/////\tdata\t/////\n"RESET);
	printf(GREEN"Phil_nbr ->"BLUE" %d\n"RESET, data->phil_nbr);
	printf(GREEN"Time_to_die ->"BLUE" %d\n"RESET, data->time_to_die);
	printf(GREEN"Time_to_eat ->"BLUE" %d\n"RESET, data->time_to_eat);
	printf(GREEN"Time_to_sleep ->"BLUE" %d\n"RESET, data->time_to_sleep);
	printf(GREEN"Must_eat ->"BLUE" %d\n"RESET, data->must_eat);
}