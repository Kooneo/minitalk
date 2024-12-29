/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:25 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/29 18:15:49 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_char(int *cab, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (cab[i] == 1)
			kill(pid, SIGUSR1);
		else if (cab[i] == 0)
			kill(pid, SIGUSR2);
		usleep(20000);
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
	ascii_to_bit('\0', pid);
	// pause();
}

void	acknowledgment_handler(int signum)
{
	if (signum == SIGUSR2)
		;
	else if (signum == SIGUSR1)
	{
		ft_printf("Server acknowledged the message.\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	int pid;
	char *message;

	if (argc == 3)
	{
		struct sigaction ack_signal;
		ack_signal.sa_handler = acknowledgment_handler;
		sigemptyset(&ack_signal.sa_mask);
		ack_signal.sa_flags = 0;
		sigaction(SIGUSR1, &ack_signal, NULL);
		sigaction(SIGUSR2, &ack_signal, NULL);

		pid = ft_atoi(argv[1]);
		message = argv[2];
		if (pid < 0 || message[0] == '\0')
			return (1);
		message_encryption(message, pid);
	} else
	{
		ft_putendl_fd("Error:", 2);
		ft_putendl_fd("Usage: <PID> <MESSAGE>", 2);
	}
	return (0);
}