/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:33:35 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/25 23:33:36 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
** Retourne -1 si le format est invalide, -2 si la valeur depasse INT_MAX.
** Accepte les espaces en tete et un '+', refuse tout le reste.
*/
long	ft_atol_custom(char *str)
{
	long	result;
	int		i;
	int		start_digit;

	if (!str)
		return (-1);
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	start_digit = i;
	while (ft_is_digit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (-2);
		i++;
	}
	if (start_digit == i || str[i] != '\0')
		return (-1);
	return (result);
}

/* Ecrit "Error: msg" sur stderr et retourne 1. */
int	ft_error(char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, "Error: ", 7);
	write(2, msg, len);
	write(2, "\n", 1);
	return (1);
}
