/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <hishembekka@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:34:56 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/26 00:38:02 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_table_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->end_lock, NULL))
		return (ft_error("failed to initialize end_lock"));
	table->end_lock_initialized = true;
	if (pthread_mutex_init(&table->write_lock, NULL))
		return (ft_error("failed to initialize write_lock"));
	table->write_lock_initialized = true;
	if (pthread_mutex_init(&table->start_lock, NULL))
		return (ft_error("failed to initialize start_lock"));
	table->start_lock_initialized = true;
	return (0);
}

static int	ft_init_fork_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (ft_error("failed to initialize a fork mutex"));
		table->nb_forks_initialized++;
		i++;
	}
	return (0);
}

/*
** Anti-deadlock : les pairs prennent gauche puis droite, les impairs
** droite puis gauche. Deux voisins ne peuvent jamais tenir chacun une
** fourchette en attendant l'autre en boucle.
*/
static void	ft_assign_forks(t_table *table, t_philo *philo, int i)
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	left = &table->forks[i];
	right = &table->forks[(i + 1) % table->nb_philo];
	philo->first_fork = right;
	philo->second_fork = left;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = left;
		philo->second_fork = right;
	}
}

static int	ft_init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->philos[i].mlock, NULL))
			return (ft_error("failed to initialize a philosopher lock"));
		table->nb_meals_locks_initialized++;
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		ft_assign_forks(table, &table->philos[i], i);
		i++;
	}
	return (0);
}

int	ft_initialize(t_table *table)
{
	if (ft_init_table_mutexes(table))
		return (1);
	if (ft_init_fork_mutexes(table))
		return (1);
	if (ft_init_philos(table))
		return (1);
	return (0);
}
