/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:25 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/07 23:09:45 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	show_error(char *msg)
{
	ft_putendl_fd("Error:", 2);
	ft_putendl_fd(msg, 2);
}

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
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				show_error("Failed to send the signal.");
		}
		usleep(2025);
		i--;
	}
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
