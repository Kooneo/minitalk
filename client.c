/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:25 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/16 19:45:56 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signals(unsigned char byte, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((byte >> i) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				show_error("⛔ Failed to send the signal.");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				show_error("⛔ Failed to send the signal.");
		}
		usleep(20205);
		i--;
	}
}

void	message_encryption(char *msg, int pid)
{
	size_t	i;

	i = 0;
	while (msg[i])
	{
		send_signals((unsigned char)msg[i], pid);
		i++;
	}
	send_signals('\n', pid);
	send_signals('\0', pid);
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
		message = argv[2];
		if (pid < 0)
			show_error("⛔ PID Can't be Negative Value.");
		if (pid < 0 || message[0] == '\0')
			return (1);
		message_encryption(message, pid);
	}
	else
		show_error("🚀 Usage: <PID> <MESSAGE>");
	return (0);
}
