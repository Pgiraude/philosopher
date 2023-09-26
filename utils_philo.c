/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:51:14 by pgiraude          #+#    #+#             */
/*   Updated: 2023/06/30 00:05:48 by pgiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(struct timeval start, int *time)
{
	struct timeval	current;
	long int		begin;
	long int		finish;

	if (gettimeofday(&current, NULL) == -1)
		return (-1);
	begin = start.tv_sec * 1000 + (start.tv_usec / 1000);
	finish = current.tv_sec * 1000 + (current.tv_usec / 1000);
	if ((finish - begin) > INT_MAX)
		return (-2);
	*time = 0;
	*time = finish - begin;
	return (0);
}

int	atoi_philo(char *str_nbr)
{
	int			i;
	long int	nbr;
	int			count;

	nbr = 0;
	i = 0;
	count = 0;
	if (!str_nbr)
		return (-1);
	while (str_nbr[i] == ' ' || str_nbr[i] == '	')
		i++;
	if (str_nbr[i] == '\0' || (str_nbr[i] == '0' && !(str_nbr[i + 1] == ' ' \
		|| str_nbr[i + 1] == '\0' || str_nbr[i + 1] == '	')))
		return (-1);
	while (str_nbr[i] >= '0' && str_nbr[i] <= '9')
	{
		nbr = nbr * 10 + (str_nbr[i] - 48);
		i++;
		count++;
	}
	while (str_nbr[i] == ' ' || str_nbr[i] == '	')
		i++;
	if (str_nbr[i] != '\0' || nbr > INT_MAX || nbr < 0 || count > 11)
		return (-2);
	return (nbr);
}

int	get_value(pthread_mutex_t *lock, int *value)
{
	int	tmp;

	pthread_mutex_lock(lock);
	tmp = *value;
	pthread_mutex_unlock(lock);
	return (tmp);
}

int	change_value(pthread_mutex_t *lock, int *value, int new_value)
{
	pthread_mutex_lock(lock);
	*value = new_value;
	pthread_mutex_unlock(lock);
	return (0);
}

void	lock_unlock(t_philo *philo, int num_philo, int mode)
{
	if (mode == TRUE)
	{
		if (num_philo % 2 != 0)
		{
			pthread_mutex_lock(&philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&philo->left_fork);
		}
		return ;
	}
	if (num_philo % 2 != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
