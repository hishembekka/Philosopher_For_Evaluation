/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <hishembekka@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:33:40 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/26 00:25:19 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (ft_error("failed to get current time"), -1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*
** usleep() seul derive : on dort par tranches de 500 us en reverifiant
** l'heure, et on sort tout de suite si la simulation s'arrete.
*/
int	ft_usleep(long time_sleep_in_ms, t_table *table)
{
	long	start_time;
	long	now;

	if (time_sleep_in_ms <= 0)
		return (0);
	start_time = ft_get_time_now();
	if (start_time == -1)
		return (ft_put_simulation_stopped(table), 1);
	now = start_time;
	while (now - start_time < time_sleep_in_ms)
	{
		if (ft_simulation_stopped(table))
			return (1);
		if (usleep(500) == -1)
			return (ft_put_simulation_stopped(table), 1);
		now = ft_get_time_now();
		if (now == -1)
			return (ft_put_simulation_stopped(table), 1);
	}
	return (0);
}
