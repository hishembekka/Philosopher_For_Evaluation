/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 16:48:37 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/25 23:35:25 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_and_join(t_table *table)
{
	long	i;

	if (table->end_lock_initialized)
	{
		pthread_mutex_lock(&table->end_lock);
		table->flag_simulation_ended = true;
		pthread_mutex_unlock(&table->end_lock);
	}
	i = 0;
	while (i < table->nb_philo_threads_initialized)
		pthread_join(table->philos[i++].thread, NULL);
	if (table->monitor_created)
		pthread_join(table->monitor, NULL);
}

static void	destroy_mutexes(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->nb_meals_locks_initialized)
		pthread_mutex_destroy(&table->philos[i++].mlock);
	i = 0;
	while (i < table->nb_forks_initialized)
		pthread_mutex_destroy(&table->forks[i++]);
	if (table->write_lock_initialized)
		pthread_mutex_destroy(&table->write_lock);
	if (table->end_lock_initialized)
		pthread_mutex_destroy(&table->end_lock);
	if (table->start_lock_initialized)
		pthread_mutex_destroy(&table->start_lock);
}

void	ft_clear(t_table *table)
{
	stop_and_join(table);
	destroy_mutexes(table);
	free(table->forks);
	table->forks = NULL;
	free(table->philos);
	table->philos = NULL;
}
