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

int	main(int argc, char **argv)
{
	t_data	*data;
	t_all	*all;

	if (argc < 5 || argc > 6)
		return (inv_args());
	if (args_verif(&argv[1]) != 0)
		return (1);
	all = malloc(sizeof(t_all));
	if (!all)
		return (1);
	data = parsing_one(argc, argv);
	if (!data)
		return (free_all_err(all));
	all = all_init(data);
	if (!all)
		return (1);
	no_zero(data);
	if (phil_init(all))
		return (1);
	free_all(all);
	return (0);
}