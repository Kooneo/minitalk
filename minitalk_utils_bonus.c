/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:10:45 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/08 20:11:05 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	show_error(char *msg)
{
	ft_putendl_fd("Error:", 2);
	ft_putendl_fd(msg, 2);
}

void	int_to_binary(int *bits, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		bits[i] = c % 2;
		c = c / 2;
		i++;
	}
}

int	binary_to_int(char *bit_set)
{
	int	decimal_value;
	int	base;
	int	i;

	base = 1;
	decimal_value = 0;
	i = 7;
	while (i >= 0)
	{
		if (bit_set[i] == '1')
			decimal_value += base;
		base = base * 2;
		i--;
	}
	return (decimal_value);
}
