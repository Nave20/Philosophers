/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:30:47 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/13 08:30:47 by vpirotti         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data	*data;
	t_all	*all;

	if (argc < 5 || argc > 6)
		return (inv_args());
	if (args_verif(&argv[1]) != 0)
		return (1);
	data = parsing_one(argc, argv);
	if (!data)
		return (1);
	all = all_init(data);
	no_zero(data);
	print_data(data);
	print_time(all);
	free_all(all);
}