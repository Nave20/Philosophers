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

	if (argc < 5 || argc > 6)
		return (inv_args());
	if (args_verif(&argv[1]) != 0)
		return (1);
	data = all_init(argc, argv);
	if (!data)
		return (1);
	if (phil_init(data))
		return (1);
	fork_init(data);
	thread_launch(data);
	free_all(data);
	return (0);
}