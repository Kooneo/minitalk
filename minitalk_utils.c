/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:10:45 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/17 13:00:04 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	show_error(char *msg)
{
	ft_putendl_fd("Error:", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
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
