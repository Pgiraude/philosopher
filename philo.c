/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:33:19 by pgiraude          #+#    #+#             */
/*   Updated: 2023/07/02 17:11:05 by pgiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int status, t_philo *philo)
{
	int	time;

	if (philo_sign(philo->param, FALSE) == FALSE)
	{
		if (status == SLEEPING)
		{
			get_time(philo->param->start, &time);
			printf("%d %d is sleeping\n", time, philo->num_philo);
		}
		if (status == THINKING)
		{
			get_time(philo->param->start, &time);
			printf("%d %d is thinking\n", time, philo->num_philo);
			pthread_mutex_unlock(&philo->param->lock_dead);
			time = (philo->param->sleep_time + philo->param->eat_time);
			if ((philo->param->die_time - time) > 0)
				usleep (((philo->param->die_time - time) / 2) * 1000);
			else
				usleep (philo->param->die_time / 2);
			return ;
		}
	}
	pthread_mutex_unlock(&philo->param->lock_dead);
}

int	is_dead(t_philo *philo, t_param *param)
{
	int	time;
	int	last_meal;

	if (philo_sign(param, FALSE) == FALSE)
	{
		get_time(param->start, &time);
		last_meal = philo->last_meal;
		if ((time - last_meal) > param->die_time)
		{
			get_time(param->start, &time);
			printf("%d %d is dead\n", time, philo->num_philo);
			param->dead = TRUE;
			pthread_mutex_unlock(&param->lock_dead);
			return (TRUE);
		}
	}
	pthread_mutex_unlock(&param->lock_dead);
	return (FALSE);
}

int	philo_sign(t_param *param, int mode)
{
	int	value;

	value = FALSE;
	pthread_mutex_lock(&param->lock_dead);
	if (param->dead == TRUE)
		value = TRUE;
	if (param->full == TRUE)
		value = TRUE;
	if (mode == TRUE)
		pthread_mutex_unlock(&param->lock_dead);
	return (value);
}

int	check_life_philo(t_philo *philo, t_param *param)
{
	int	index;
	int	nbr_philo;

	nbr_philo = get_value(&param->lock_value, &param->nbr_philo);
	while (philo_sign(param, TRUE) == FALSE)
	{
		index = 0;
		while (index < nbr_philo)
		{
			if (is_dead(&philo[index], param) == TRUE)
				return (0);
			index++;
		}
		usleep(1000);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_param			*param;
	struct timeval	start;

	param = malloc(sizeof(t_param));
	if (init_philo(argc, argv, param, &philo) != 0)
		return (free (param), 1);
	gettimeofday(&start, NULL);
	param->start = start;
	if (launch_philo(param, philo) != 0)
		return (free (param), free (philo), 2);
	check_life_philo(philo, param);
	exit_philo(philo, param);
}
