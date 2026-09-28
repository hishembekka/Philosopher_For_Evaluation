/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:33:55 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/25 23:33:56 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_create_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				ft_philo_routine, &table->philos[i]))
			return (ft_put_simulation_stopped(table),
				ft_error("failed to create a philosopher thread"));
		table->nb_philo_threads_initialized++;
		i++;
	}
	return (0);
}

static int	ft_create_monitor_thread(t_table *table)
{
	if (pthread_create(&table->monitor, NULL, ft_monitor_routine, table))
		return (ft_put_simulation_stopped(table),
			ft_error("failed to create the monitor thread"));
	table->monitor_created = true;
	return (0);
}

/*
** Appelee quand tous les threads attendent : start_time et last_meal
** partent du meme instant pour tout le monde.
*/
static int	ft_set_start_time(t_table *table)
{
	long	now;
	int		i;

	now = ft_get_time_now();
	if (now == -1)
		return (ft_put_simulation_stopped(table), 1);
	table->start_time = now;
	i = 0;
	while (i < table->nb_philo)
		table->philos[i++].last_meal = now;
	return (0);
}

/*
** 1. cree tous les threads (ils se bloquent dans ft_wait_start_or_end)
** 2. attend qu'ils soient tous prets (nb_philo + le monitor)
** 3. fixe l'heure de depart puis leve start_ready
** 4. attend la fin du monitor (mort ou tous rassasies)
** Avec 0 repas demande, tout le monde a deja fini : on ne lance rien.
*/
int	ft_simulation(t_table *table)
{
	if (table->nb_time_to_eat == 0)
		return (0);
	if (ft_create_philo_threads(table))
		return (1);
	if (ft_create_monitor_thread(table))
		return (1);
	while (!ft_all_philos_ready(table))
	{
		if (ft_simulation_stopped(table))
			return (1);
		if (usleep(500) == -1)
			return (ft_put_simulation_stopped(table), 1);
	}
	if (ft_set_start_time(table))
		return (1);
	pthread_mutex_lock(&table->start_lock);
	table->start_ready = true;
	pthread_mutex_unlock(&table->start_lock);
	if (pthread_join(table->monitor, NULL))
		return (ft_put_simulation_stopped(table), 1);
	table->monitor_created = false;
	return (0);
}
