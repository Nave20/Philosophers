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
# define FORK "\033[33m has taken a fork\033[0m\n"
# define EAT "\033[0;32m is eating\033[0m\n"
# define SLEEP "\033[34m is sleeping\033[0m\n"
# define THINK "\033[38;5;205m is thinking\033[0m\n"
# define DIED "\033[31m\033[1m died\033[0m\n"

//-------------------------------INCLUDE-------------------------------
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>

//--------------------------------ENUM---------------------------------
typedef enum e_status
{
	ALIVE,
	DEAD,
}	t_status;

typedef enum e_lock
{
	UNLOCK,
	LOCK,
}	t_lock;

//-------------------------------STRUCTS-------------------------------

typedef struct s_phil	t_phil;

typedef struct s_data
{
	long				start_time;
	int					phil_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int					error;
	t_status			schrodinger;
	pthread_mutex_t		monitor;
	pthread_mutex_t		print;
	pthread_mutex_t		*fork_mutex;
	t_phil				**phil;
}	t_data;

typedef struct s_phil
{
	pthread_t			thread;
	pthread_mutex_t		meal_mutex;
	int					id;
	int					meal_eaten;
	long				last_meal;
	pthread_mutex_t		*forks[2];
	t_data				*data;
}	t_phil;

//-------------------------------PARSING-------------------------------
t_data	*parsing_one(int argc, char **argv);
int		args_verif(char **argv);
int		no_zero(t_data *data);

//--------------------------------ERRORS-------------------------------
int		inv_args(void);
int		inv_args_bis(t_data *data, const char *str);
int		inv_args_third(const char *str);

//--------------------------------UTILS--------------------------------
void	print_data(t_data *data);
void	ft_sleep(int time);
size_t	ft_strlen(const char *str);
void	ft_putendl_fd(const char *s, int fd);
int		ft_putstr_fd(const char *s, int fd);

//--------------------------------TIME---------------------------------
long	get_time(void);

//--------------------------------FREE---------------------------------
void	free_phil(t_data *data);
void	free_data(t_data *data);
void	free_all(t_data *data);
int		exit_init(t_data *data, int max);
int		exit_phil(t_data *data);

//--------------------------------INIT---------------------------------
t_data	*all_init(int argc, char **argv);
t_phil	*phil_init_bis(t_data *data, int i);
int		phil_init(t_data *data);
void	fork_init(t_data *data);

//--------------------------------MUTEX--------------------------------
int		handle_mutex(pthread_mutex_t *mutex, t_lock	status);
int		get_status(t_data *data);

//-------------------------------ROUTINE--------------------------------
void	*phil_routine(void *args);
void	update_phil(t_phil *phil);

//-------------------------------THREAD---------------------------------
int		thread_launch(t_data *data);

//-------------------------------THREAD---------------------------------
void	print_mutex(const char *str, t_phil phil);

//-------------------------------THREAD---------------------------------
void	*monitor_rout(void *arg);

//--------------------------------ALONE---------------------------------
void	*phil_alone(t_phil *phil);

#endif