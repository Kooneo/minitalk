/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:04 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/07 23:00:52 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	bit_set[8];

void	show_error(char *msg)
{
	ft_putendl_fd("Error:", 2);
	ft_putendl_fd(msg, 2);
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

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int		index = 0;
	char			decoded_char;
	static pid_t	client_pid = 0;

	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (signum == SIGUSR1)
		bit_set[index] = '1';
	else if (signum == SIGUSR2)
		bit_set[index] = '0';
	index++;
	if (index == 8)
	{
		decoded_char = (char)binary_to_int(bit_set);
		if (decoded_char == '\0')
		{
			client_pid = 0;
			index = 0;
			ft_bzero(bit_set, sizeof(bit_set));
			return ;
		}
		write(1, &decoded_char, 1);
		ft_bzero(bit_set, sizeof(bit_set));
		index = 0;
		decoded_char = 0;
	}
	if (kill(client_pid, SIGUSR2) == -1)
		show_error("Failed to send signal");
}

int	main(void)
{
	struct sigaction signal_received;
	signal_received.sa_sigaction = signal_handler;
	sigemptyset(&signal_received.sa_mask);
	signal_received.sa_flags = SA_SIGINFO;

	ft_bzero(bit_set, sizeof(bit_set));
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}