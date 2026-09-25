/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 14:23:46 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/25 22:00:00 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (ft_parsing_validate(&table, argc, argv))
		return (1);
	if (ft_initialize(&table))
		return (ft_clear(&table), 1);
	if (ft_simulation(&table))
		return (ft_clear(&table), 1);
	ft_clear(&table);
	return (0);
}
