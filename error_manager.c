/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:32:59 by pgiraude          #+#    #+#             */
/*   Updated: 2023/06/30 00:35:17 by pgiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_manager_init(int error_code, char *msg)
{
	if (error_code == -3)
		printf("Error %d: Value is supperior too int max\n", error_code);
	if (error_code == -2)
		printf("Error %d: Bad value, need a positive decimal int\n", error_code);
	if (error_code == -1)
		printf("Error %d: No value, need a positive decimal int\n", error_code);
	if (error_code == 1)
		printf("Error %d: Need more arguments\n", error_code);
	if (error_code == 2)
		printf("Error %d: Need less arguments\n", error_code);
	if (error_code == 3)
		printf("Error %d: Malloc failde\n", error_code);
	if (error_code == 4 || error_code == 5)
		printf("Error %d: %s must be an int superior to 0\n", error_code, msg);
	if (error_code >= 6 && error_code <= 7)
		printf("Error %d: %s must be an int superior to -1\n", error_code, msg);
	if (error_code == 8)
	{
		printf("Error %d: Number of eat by philo ", error_code);
		printf("if define must be an int superior to -1\n");
	}
	if (error_code == 9)
		printf("Number of eat by philo should be superior to 0\n");
	return (error_code);
}

int	error_manager(int error_code, char *msg)
{
	if (error_code == 0)
		return (error_code);
	if (error_code < 20)
		return (error_manager_init(error_code, msg));
	if (error_code == 20)
		printf("Error %d: Failed create threads\n", error_code);
	if (error_code == 30)
		printf("Error %d: Failed init_mutex 0\n", error_code);
	if (error_code == 31)
		printf("Error %d: Failed init_mutex 1\n", error_code);
	if (error_code == 32)
		printf("Error %d: Failed lock_mutex\n", error_code);
	if (error_code == 40)
		printf("Error %d: Failed thread_join\n", error_code);
	if (error_code == 41)
		printf("Error %d: Failed fork_mutex_destroy\n", error_code);
	if (error_code == 42)
		printf("Error %d: Failed lock_mutex_destroy\n", error_code);
	return (error_code);
}
