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

int	ft_atoi(const char *str, t_all *all)
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
			return (inv_args_bis(all, str));
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res);
}

t_all	*parsing_one(int argc, char **argv)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	all->error = 0;
	all->phil_nbr = ft_atoi(argv[1], all);
	all->time_to_die = ft_atoi(argv[2], all);
	all->time_to_eat = ft_atoi(argv[3], all);
	all->time_to_sleep = ft_atoi(argv[4], all);
	if (argc == 5)
		all->must_eat = -1;
	else
		all->must_eat = ft_atoi(argv[5], all);
	if (all->error == 1)
	{
		free(all);
		return (NULL);
	}
	return (all);
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

void	no_zero(t_all *all)
{
	if (all->must_eat == 0 || all->phil_nbr == 0 || all->time_to_die == 0
		|| all->time_to_eat == 0 || all->time_to_sleep == 0)
	{
		ft_putendl_fd(RED"invalid arguments : arguments cannot "
				   "be equal to 0."RESET, 2);
		free(all);
		exit(EXIT_FAILURE);
	}
}