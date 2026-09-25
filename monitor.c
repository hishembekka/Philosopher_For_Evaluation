/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:34:25 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/25 23:34:26 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Le "died" est affiche en tenant mlock : le philo ne peut pas mettre a
** jour last_meal entre la verification et l'annonce de sa mort.
** Retourne 1 si la simulation doit s'arreter.
*/
static int	ft_check_philo(t_philo *philo, int *finished)
{
	long	now;

	pthread_mutex_lock(&philo->mlock);
	now = ft_get_time_now();
	if (now == -1)
		return (pthread_mutex_unlock(&philo->mlock),
			ft_put_simulation_stopped(philo->table), 1);
	if (now - philo->last_meal >= philo->table->time_to_die)
		return (ft_print_status(philo, "died", true),
			pthread_mutex_unlock(&philo->mlock), 1);
	if (philo->table->nb_time_to_eat > 0
		&& philo->meals_eaten >= philo->table->nb_time_to_eat)
		(*finished)++;
	pthread_mutex_unlock(&philo->mlock);
	return (0);
}

/*
** Toutes les ~1 ms : verifie chaque philo. S'arrete a la premiere mort,
** ou quand tous ont mange au moins nb_time_to_eat fois.
*/
void	*ft_monitor_routine(void *arg)
{
	t_table	*table;
	int		finished;
	int		i;

	table = (t_table *)arg;
	ft_add_ready_count(table);
	if (ft_wait_start_or_end(table))
		return (NULL);
	while (!ft_simulation_stopped(table))
	{
		finished = 0;
		i = 0;
		while (i < table->nb_philo)
		{
			if (ft_check_philo(&table->philos[i], &finished))
				return (NULL);
			i++;
		}
		if (table->nb_time_to_eat > 0 && finished == table->nb_philo)
			return (ft_put_simulation_stopped(table), NULL);
		if (usleep(1000) == -1)
			return (ft_put_simulation_stopped(table), NULL);
	}
	return (NULL);
}
