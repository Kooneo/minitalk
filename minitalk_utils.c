/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:02:55 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/31 19:14:20 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	show_error(char *err)
{
	ft_putendl_fd("Error:", 2);
	ft_putendl_fd(err, 2);
	exit(1);
}

void	int_to_binary(int *bits, char c)
{
	int	i;

	i = 0;
	while (i < 8)
		bits[i++] = 0;
	i = 0;
	while (c > 0)
	{
		bits[i] = c % 2;
		c = c / 2;
		i++;
	}
}

int	binary_to_int(int *bit_set)
{
	int	decimal_value;
	int	base;
	int	i;

	base = 1;
	decimal_value = 0;
	i = 7;
	while (i >= 0)
	{
		if (bit_set[i] == 1)
			decimal_value += base;
		base = base * 2;
		i--;
	}
	return (decimal_value);
}
