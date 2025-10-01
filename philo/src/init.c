/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:14:37 by vpirotti          #+#    #+#             */
/*   Updated: 2025/10/01 14:48:24 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	data_init(t_data *data, int i)
{
	data->schrodinger = ALIVE;
	if (pthread_mutex_init(&data->monitor, NULL))
		return (1);
	if (pthread_mutex_init(&data->print, NULL))
	{
		pthread_mutex_destroy(&data->monitor);
		return (1);
	}
	data->fork = malloc(data->phil_nbr * sizeof(t_fork));
	if (!data->fork)
	{
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->monitor);
		return (1);
	}
	while (i < data->phil_nbr)
	{
		data->fork[i].fork_lock = UNLOCK;
		if (pthread_mutex_init(&data->fork[i].fork_mutex, NULL))
			return (exit_init(data, i));
		i++;
	}
	return (0);
}

void	fork_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phil_nbr)
	{
		if (i == 0)
		{
			data->phil[i]->forks[0] = &data->fork[i];
			data->phil[i]->forks[1] = &data->fork[data->phil_nbr - 1];
		}
		else
		{
			data->phil[i]->forks[0] = &data->fork[i];
			data->phil[i]->forks[1] = &data->fork[i - 1];
		}
		i++;
	}
}

t_data	*all_init(int argc, char **argv)
{
	t_data	*data;

	data = parsing_one(argc, argv);
	if (!data)
		return (NULL);
	no_zero(data);
	if (data_init(data, 0))
	{
		free(data);
		return (NULL);
	}
	return (data);
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
	phil->last_meal = 0;
	phil->data = data;
	phil->id = i;
	phil->meal_eaten = 0;
	return (phil);
}

int	phil_init(t_data *data)
{
	int		i;
	t_phil	**phil;

	i = 0;
	phil = malloc((data->phil_nbr + 1) * sizeof(t_phil **));
	data->phil = phil;
	if (!data->phil)
		return (exit_phil(data));
	while (i < data->phil_nbr)
	{
		data->phil[i] = NULL;
		i++;
	}
	i = 0;
	while (i < data->phil_nbr)
	{
		data->phil[i] = phil_init_bis(data, i);
		if (!data->phil[i])
		{
			free_all(data);
			return (1);
		}
		i++;
	}
	return (0);
}
