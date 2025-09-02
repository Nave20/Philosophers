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

t_all	*all_init(t_data *data)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	all->start_time = get_time();
	all->data = data;
	return (all);
}

t_phil	*phil_init_bis(t_data *data, int i)
{
	t_phil	*phil;

	phil = malloc(sizeof(t_phil));
	if (!phil)
		return (NULL);
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