/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:34:21 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/25 23:34:22 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Les 4 premiers arguments : entiers strictement positifs <= INT_MAX.
** Le 5e (nb_time_to_eat) est optionnel et peut valoir 0 :
** -1 = pas de limite, 0 = simulation terminee avant de commencer.
*/
static int	ft_parse_args(t_table *table, int argc, char **argv)
{
	long	values[5];
	int		i;

	if (argc != 5 && argc != 6)
		return (ft_error("wrong number of arguments"));
	i = -1;
	while (++i < argc - 1)
	{
		values[i] = ft_atol_custom(argv[i + 1]);
		if (values[i] == -1)
			return (ft_error("arguments must be positive integers"));
		if (values[i] == -2)
			return (ft_error("value exceeds INT_MAX"));
		if (values[i] == 0 && i < 4)
			return (ft_error("values must be strictly positive"));
	}
	table->nb_philo = values[0];
	table->time_to_die = values[1];
	table->time_to_eat = values[2];
	table->time_to_sleep = values[3];
	table->nb_time_to_eat = -1;
	if (argc == 6)
		table->nb_time_to_eat = values[4];
	return (0);
}

int	ft_parsing_validate(t_table *table, int argc, char **argv)
{
	memset(table, 0, sizeof(t_table));
	if (ft_parse_args(table, argc, argv))
		return (1);
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (ft_error("philosophers allocation failed"));
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
	{
		free(table->philos);
		table->philos = NULL;
		return (ft_error("forks allocation failed"));
	}
	return (0);
}
