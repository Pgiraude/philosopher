/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:32:50 by pgiraude          #+#    #+#             */
/*   Updated: 2023/06/30 00:24:08 by pgiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_error_threads(t_philo *philo, t_param *param, int value)
{
	int	index;
	int	nbr_philo;

	index = value;
	nbr_philo = get_value(&param->lock_value, &param->nbr_philo);
	while (--index >= 0)
	{
		if (pthread_join(philo[index].thread, NULL) != 0)
			error_manager(40, NULL);
	}
	index = -1;
	while (++index < nbr_philo)
	{
		if (pthread_mutex_destroy(&philo[index].left_fork) != 0)
			error_manager(41, NULL);
	}
	if (pthread_mutex_destroy(&param->lock_dead) != 0)
		error_manager(42, NULL);
	if (pthread_mutex_destroy(&param->lock_value) != 0)
		error_manager(42, NULL);
	free (philo);
	free (param);
	return (0);
}

int	exit_philo(t_philo *philo, t_param *param)
{
	int	index;
	int	nbr_philo;

	index = -1;
	nbr_philo = get_value(&param->lock_value, &param->nbr_philo);
	while (++index < nbr_philo)
	{
		if (pthread_join(philo[index].thread, NULL) != 0)
			error_manager(40, NULL);
	}
	index = -1;
	while (++index < nbr_philo)
	{
		if (pthread_mutex_destroy(&philo[index].left_fork) != 0)
			error_manager(41, NULL);
	}
	if (pthread_mutex_destroy(&param->lock_dead) != 0)
		error_manager(42, NULL);
	if (pthread_mutex_destroy(&param->lock_value) != 0)
		error_manager(42, NULL);
	free (philo);
	free (param);
	return (0);
}
