/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:04 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/31 19:14:29 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		bit_set[8];

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	index = 0;
	char		decoded_char;
	pid_t		client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (signum == SIGUSR1)
		bit_set[index] = 1;
	else if (signum == SIGUSR2)
		bit_set[index] = 0;
	index++;
	if (index == 8)
	{
		decoded_char = (char)binary_to_int(bit_set);
		if (decoded_char == '\0')
		{
			index = 0;
			return ;
		}
		write(1, &decoded_char, 1);
		index = 0;
	}
	if (kill(client_pid, SIGUSR2) == -1)
		show_error("Fail Send The Signal.");
}

int	main(void)
{
	struct sigaction	signal_received;

	signal_received.sa_sigaction = signal_handler;
	sigemptyset(&signal_received.sa_mask);
	signal_received.sa_flags = SA_SIGINFO;
	ft_bzero(bit_set, 8);
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}
