/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:04 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/14 18:34:19 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	g_bit_set[8];

void	update_bit_set(int signum, int *index)
{
	if (signum == SIGUSR1)
		g_bit_set[*index] = '1';
	else if (signum == SIGUSR2)
		g_bit_set[*index] = '0';
	(*index)++;
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int		index = 0;
	char			decoded_char;
	static pid_t	client_pid = 0;

	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	update_bit_set(signum, &index);
	if (index == 8)
	{
		decoded_char = binary_to_int(g_bit_set);
		if (decoded_char == '\0')
		{
			client_pid = 0;
			index = 0;
			ft_bzero(g_bit_set, sizeof(g_bit_set));
			return ;
		}
		write(1, &decoded_char, 1);
		ft_bzero(g_bit_set, sizeof(g_bit_set));
		index = 0;
		decoded_char = 0;
	}
	if (kill(client_pid, SIGUSR2) == -1)
		show_error("⛔ Failed to send signal");
}

int	main(void)
{
	struct sigaction	signal_received;

	signal_received.sa_sigaction = signal_handler;
	signal_received.sa_flags = SA_SIGINFO;
	ft_bzero(g_bit_set, sizeof(g_bit_set));
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	ft_printf("🚀 Server PID: %d\n", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}
