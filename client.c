/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:25 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/29 19:34:59 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	show_error(char *err)
{
	ft_putendl_fd("Error:", 2);
	ft_putendl_fd(err, 2);
	exit(1);
}

void	send_char(int *cab, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (cab[i] == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				show_error("Failed to send the signal.");
		}
		else if (cab[i] == 0)
		{
			if (kill(pid, SIGUSR2) == -1)
				show_error("Failed to send the signal");
		}
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
		ack_signal.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &ack_signal, NULL);
		sigaction(SIGUSR2, &ack_signal, NULL);
		pid = ft_atoi(argv[1]);
		if (pid < 0)
			show_error("PID Can't be Negative Value.");
		message = argv[2];
		if (pid < 0 || message[0] == '\0')
			return (1);
		message_encryption(message, pid);
	}
	else
		show_error("Usage: <PID> <MESSAGE>");
	return (0);
}
