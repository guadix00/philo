/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:35:23 by gualvare          #+#    #+#             */
/*   Updated: 2025/03/26 14:51:51 by gualvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	ft_atoi(char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result * sign > INT_MAX)
			return (INT_MAX);
		if (result * sign < INT_MIN)
			return (INT_MIN);
		str++;
	}
	return ((int)(result * sign));
}

static	int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static	int	is_number(char *str)
{
	if (*str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!is_digit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	arg_checker(char **argv)
{
	int	num;
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_number(argv[i]))
			return (1);
		num = ft_atoi(argv[i]);
		if (num < 0)
			return (1);
		if (num == INT_MAX || num == INT_MIN)
			return (1);
		if ((i == 1 && num > 200) || (num < 1))
		{
			printf("Wrong number of philosophers\n");
			return (1);
		}
		i++;
	}
	return (0);
}
