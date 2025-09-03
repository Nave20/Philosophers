/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:06:42 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/19 12:06:42 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"
#include "limits.h"

int	ft_atoi(const char *str, t_data *data)
{
	int	res;
	int	digit;
	int	i;

	i = 0;
	res = 0;
	while ((str[i] > 47 && str[i] < 58))
	{
		digit = str[i] - 48;
		if ((res > (INT_MAX - digit) / 10))
			return (inv_args_bis(data, str));
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res);
}

t_data	*parsing_one(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->error = 0;
	data->phil_nbr = ft_atoi(argv[1], data);
	data->time_to_die = ft_atoi(argv[2], data);
	data->time_to_eat = ft_atoi(argv[3], data);
	data->time_to_sleep = ft_atoi(argv[4], data);
	if (argc == 5)
		data->must_eat = -1;
	else
		data->must_eat = ft_atoi(argv[5], data);
	if (data->error == 1)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

int	args_verif(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				inv_args_third(argv[i]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	no_zero(t_data *data)
{
	if (data->must_eat == 0 || data->phil_nbr == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0)
	{
		ft_putendl_fd(RED"invalid arguments : arguments cannot "
			"be equal to 0."RESET, 2);
		return (1);
	}
	return (0);
}
