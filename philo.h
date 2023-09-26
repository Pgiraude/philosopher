/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:06:23 by pgiraude          #+#    #+#             */
/*   Updated: 2023/06/29 23:51:43 by pgiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define EATING 4
# define SLEEPING 5
# define THINKING 6
# define DEAD 7

typedef enum e_bool
{
	FALSE,
	TRUE
}t_bool;

typedef struct s_param
{
	int				nbr_philo;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				nbr_eat_full;
	int				dead;
	int				full;
	int				count_full;
	struct timeval	start;
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_value;
}t_param;

typedef struct s_philo
{	
	pthread_t		thread;
	int				num_philo;
	int				nbr_eat;
	int				last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	struct s_param	*param;
}t_philo;

int		init_philo(int argc, char **argv, t_param *data, t_philo **philo);

int		launch_philo(t_param *param, t_philo *philo);

int		get_time(struct timeval start, int *time);
void	print_status(int status, t_philo *philo);
int		check_life_philo(t_philo *philo, t_param *param);
int		philo_sign(t_param *param, int mode);

int		atoi_philo(char *str_nbr);
int		get_value(pthread_mutex_t *lock, int *value);
int		change_value(pthread_mutex_t *lock, int *value, int new_value);
void	lock_unlock(t_philo *philo, int num_philo, int mode);

int		exit_philo(t_philo *philo, t_param *param);
int		exit_error_threads(t_philo *philo, t_param *param, int value);

int		error_manager(int error_code, char *msg);

#endif