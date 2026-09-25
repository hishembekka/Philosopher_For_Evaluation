/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:33:50 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/25 23:43:23 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_simulation_stopped(t_table *table)
{
	bool	flag;

	pthread_mutex_lock(&table->end_lock);
	flag = table->flag_simulation_ended;
	pthread_mutex_unlock(&table->end_lock);
	return (flag);
}

void	ft_put_simulation_stopped(t_table *table)
{
	pthread_mutex_lock(&table->end_lock);
	table->flag_simulation_ended = true;
	pthread_mutex_unlock(&table->end_lock);
}

void	ft_add_ready_count(t_table *table)
{
	pthread_mutex_lock(&table->start_lock);
	table->ready_count++;
	pthread_mutex_unlock(&table->start_lock);
}

/* Bloque le thread jusqu'au signal de depart (0) ou un arret (1). */
int	ft_wait_start_or_end(t_table *table)
{
	bool	start;

	while (1)
	{
		pthread_mutex_lock(&table->start_lock);
		start = table->start_ready;
		pthread_mutex_unlock(&table->start_lock);
		if (ft_simulation_stopped(table))
			return (1);
		if (start)
			return (0);
		if (usleep(1000) == -1)
			return (ft_put_simulation_stopped(table), 1);
	}
}

/* nb_philo threads philosophes + 1 thread monitor. */
int	ft_all_philos_ready(t_table *table)
{
	bool	ready;

	pthread_mutex_lock(&table->start_lock);
	ready = (table->ready_count == table->nb_philo + 1);
	pthread_mutex_unlock(&table->start_lock);
	return (ready);
}
