/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:25 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/31 19:14:51 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signals(int *cab, int pid)
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
				show_error("Failed to send the signal.");
		}
		usleep(20000);
		i--;
	}
}

void	send_char(char c, int *bits, pid_t pid)
{
	int_to_binary(bits, c);
	send_signals(bits, pid);
}

void	message_encryption(char *msg, int pid)
{
	size_t	i;
	int		bits[8];

	i = 0;
	while (i < ft_strlen(msg))
	{
		send_char(msg[i], bits, pid);
		i++;
	}
	send_char('\n', bits, pid);
	send_char('\0', bits, pid);
}

void	signal_handler(int signum)
{
	if (signum == SIGUSR2)
		;
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc == 3)
	{
		signal(SIGUSR2, signal_handler);
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
