/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:14:37 by vpirotti          #+#    #+#             */
/*   Updated: 2025/09/02 12:14:37 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	data_init(t_data *data) //SECURE
{
	int	i;

	i = 0;
	data->start_time = get_time();
	data->schrodinger = ALIVE;
	if (pthread_mutex_init(&data->monitor, NULL))
		return (1);
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	data->fork_mutex = malloc(data->phil_nbr * sizeof(pthread_mutex_t*));
	if (!data->fork_mutex)
		return (1);
	while (i < data->phil_nbr)
	{
		if (pthread_mutex_init(&data->fork_mutex[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

t_all	*all_init(int argc, char **argv)
{
	t_all	*all;
	t_data	*data;

	data = parsing_one(argc, argv);
	if (!data)
		return (NULL);
	data_init(data);
	all = malloc(sizeof(t_all));
	if (!all)
		{;}
	no_zero(data);
	all->data = data;
	return (all);
}

t_phil	*phil_init_bis(t_data *data, int i)
{
	t_phil	*phil;

	phil = malloc(sizeof(t_phil));
	if (!phil)
		return (NULL);
	if (pthread_mutex_init(&phil->meal_mutex, NULL))
	{
		free(phil);
		return (NULL);
	}
	phil->data = data;
	phil->id = i;
	phil->meal_eaten = 0;
	phil->forks[0] = 1;
	phil->forks[1] = 0;
	return (phil);
}

int	phil_init(t_all *all)
{
	int		i;
	t_phil	**phil;

	i = 0;
	phil = malloc((all->data->phil_nbr + 1) * sizeof(t_phil**));
	all->phil = phil;
	if (!all->phil)
		return (1);
	while (i < all->data->phil_nbr)
	{
		all->phil[i] = NULL;
		i++;
	}
	i = 0;
	while (i < all->data->phil_nbr)
	{
		all->phil[i] = phil_init_bis(all->data, i);
		if (!all->phil[i])
		{
			free_phil(all);
			return (1);
		}
		i++;
	}
	return (0);
}