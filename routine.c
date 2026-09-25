/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:34:04 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/25 23:34:04 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Les impairs demarrent avec time_to_eat / 2 de retard : les pairs
** mangent d'abord, ce qui evite que tout le monde se jette sur les
** fourchettes au meme instant.
*/
void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_add_ready_count(philo->table);
	if (ft_wait_start_or_end(philo->table))
		return (NULL);
	if (philo->table->nb_philo > 1 && philo->id % 2 != 0)
		if (ft_usleep(philo->table->time_to_eat / 2, philo->table))
			return (NULL);
	while (!ft_simulation_stopped(philo->table))
	{
		if (ft_eat(philo) || ft_sleep(philo) || ft_think(philo))
			break ;
	}
	return (NULL);
}
