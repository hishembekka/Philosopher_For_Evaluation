/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <hishembekka@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:35:05 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/26 00:38:02 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	if (ft_print_status(philo, "has taken a fork", false))
		return (pthread_mutex_unlock(philo->first_fork), 1);
	pthread_mutex_lock(philo->second_fork);
	if (ft_print_status(philo, "has taken a fork", false))
		return (ft_release_forks(philo), 1);
	return (0);
}

void	ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

/*
** Un seul philo = une seule fourchette : il la prend puis attend que
** le monitor constate sa mort. Retourne toujours 1 pour sortir de la boucle.
*/
int	ft_eat_alone(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	ft_print_status(philo, "has taken a fork", false);
	while (!ft_simulation_stopped(philo->table))
	{
		if (usleep(1000) == -1)
		{
			ft_put_simulation_stopped(philo->table);
			break ;
		}
	}
	pthread_mutex_unlock(philo->first_fork);
	return (1);
}
