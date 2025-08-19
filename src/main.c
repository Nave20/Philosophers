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
	t_all	*all;

	if (argc < 5 || argc > 6)
		return (inv_args());
	if (args_verif(&argv[1]) != 0)
		return (1);
	all = parsing_one(argc, argv);
	if (!all)
		return (1);
	print_all(all);
	printf(BLUE"Hello World\n"RESET);
}