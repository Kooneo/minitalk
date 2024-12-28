/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:25 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/28 18:45:53 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

// void	print_bits(int *bits)
// {
// 	for (int j = 8 - 1; j >= 0; j--)
// 		ft_printf("%d", bits[j]);
// }

void	send_char(int *cab, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (cab[i])
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		ft_printf("%d", cab[i]);
		i--;
	}
}

void	ascii_to_bit(char c, int pid)
{
	int	bits[8];
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
	send_char(bits, pid);
}

void	message_encryption(char *msg, int pid)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(msg))
	{
		ascii_to_bit(msg[i], pid);
		i++;
	}
}

int main(int argc, char **argv)
{
	int     pid;
	char    *message;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		message = argv[2];
		if (pid < 0 || !message || message[0] == '\0')
			return (1);
		message_encryption(message, pid);
	}
}