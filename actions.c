/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:35:37 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/25 23:35:38 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** last_meal est mis a jour sous mlock AVANT d'afficher "is eating" :
** le monitor ne peut pas lire une valeur a moitie a jour.
** Si le philo est deja mort, il ne mange pas : le monitor annoncera la mort.
*/
static int	ft_start_meal(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->mlock);
	now = ft_get_time_now();
	if (now == -1)
		return (pthread_mutex_unlock(&philo->mlock),
			ft_put_simulation_stopped(philo->table), 1);
	if (now - philo->last_meal >= philo->table->time_to_die)
		return (pthread_mutex_unlock(&philo->mlock), 1);
	philo->last_meal = now;
	pthread_mutex_unlock(&philo->mlock);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	bool	quota_reached;

	if (philo->table->nb_philo == 1)
		return (ft_eat_alone(philo));
	if (ft_take_forks(philo))
		return (1);
	if (ft_start_meal(philo)
		|| ft_print_status(philo, "is eating", false)
		|| ft_usleep(philo->table->time_to_eat, philo->table))
		return (ft_release_forks(philo), 1);
	pthread_mutex_lock(&philo->mlock);
	philo->meals_eaten++;
	quota_reached = (philo->table->nb_time_to_eat > 0
			&& philo->meals_eaten >= philo->table->nb_time_to_eat);
	pthread_mutex_unlock(&philo->mlock);
	ft_release_forks(philo);
	return (quota_reached);
}

int	ft_sleep(t_philo *philo)
{
	if (ft_print_status(philo, "is sleeping", false))
		return (1);
	return (ft_usleep(philo->table->time_to_sleep, philo->table));
}

/*
** Nombre pair : pas d'attente, les deux groupes alternent naturellement.
** Nombre impair : un cycle doit durer au moins 3 * time_to_eat pour que
** chacun ait son tour, donc think = 2 * eat - sleep (si positif).
*/
int	ft_think(t_philo *philo)
{
	long	time_to_think;

	if (ft_print_status(philo, "is thinking", false))
		return (1);
	if (philo->table->nb_philo % 2 == 0)
		return (0);
	time_to_think = philo->table->time_to_eat * 2
		- philo->table->time_to_sleep;
	if (time_to_think > 0)
		return (ft_usleep(time_to_think, philo->table));
	return (0);
}
