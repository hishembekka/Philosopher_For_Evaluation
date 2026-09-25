/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:34:11 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/25 23:34:12 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Tout se passe sous write_lock : si died est vrai, on leve le flag de fin
** AVANT d'afficher, donc aucun autre message ne peut suivre "died".
*/
int	ft_print_status(t_philo *philo, char *status, bool died)
{
	long	now;

	pthread_mutex_lock(&philo->table->write_lock);
	if (ft_simulation_stopped(philo->table))
		return (pthread_mutex_unlock(&philo->table->write_lock), 1);
	if (died)
		ft_put_simulation_stopped(philo->table);
	now = ft_get_time_now();
	if (now == -1)
		return (ft_put_simulation_stopped(philo->table),
			pthread_mutex_unlock(&philo->table->write_lock), 1);
	printf("%ld %d %s\n", now - philo->table->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->table->write_lock);
	return (0);
}
