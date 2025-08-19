/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:31:36 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/13 08:32:49 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define CLEAR "\033[H\033[J"
# define YELLOW "\033[33m"
# define RESET "\033[0m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define RED "\033[31m"
# define BOLD "\033[1m"
# define GREEN "\033[0;32m"

//-------------------------------INCLUDE-------------------------------
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

//-------------------------------STRUCTS-------------------------------
typedef struct s_phil
{

} t_phil;

typedef struct s_all
{
	int	phil_nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	int	error;
} t_all;

//-------------------------------PARSING-------------------------------
t_all	*parsing_one(int argc, char **argv);
int		args_verif(char **argv);
void	no_zero(t_all *all);

//--------------------------------ERRORS-------------------------------
int		inv_args(void);
int		inv_args_bis(t_all *all, const char *str);
int		inv_args_third(const char *str);

//--------------------------------UTILS--------------------------------
void	print_all(t_all *all);
size_t	ft_strlen(const char *str);
void	ft_putendl_fd(const char *s, int fd);
int		ft_putstr_fd(const char *s, int fd);

#endif