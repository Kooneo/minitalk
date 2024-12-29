/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:04 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/29 20:27:31 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <stdio.h>
#include <sys/time.h>

int	bit_set[8];
static struct timeval start_time, end_time;

int	binary_to_int(int *bit_set)
{
	int	decimal_value;
	int	base;
	int	i;

	base = 1;
	decimal_value = 0;
	i = 7;
	while (i >= 0)
	{
		if (bit_set[i] == 1)
			decimal_value += base;
		base = base * 2;
		i--;
	}
	return (decimal_value);
}

void	fail_signal(void)
{
	ft_putendl_fd("Error:", 2);
	ft_putendl_fd("Fail Send The Signal.", 2);
	exit(1);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int		index = 0;
	char			decoded_char;
	static pid_t	client_pid = 0;
	long			seconds;
	long			microseconds;
	double			elapsed;

	(void)context;
	if (client_pid == 0)
	{
		client_pid = info->si_pid;
		gettimeofday(&start_time, NULL);
	}
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
			gettimeofday(&end_time, NULL); // Record end time
			ft_printf("\nMessage received completely.\n");
			seconds = end_time.tv_sec - start_time.tv_sec;
			microseconds = end_time.tv_usec - start_time.tv_usec;
			elapsed = seconds + microseconds * 1e-6;
			printf("Runtime: %.6f seconds\n", elapsed);
			if (kill(client_pid, SIGUSR1) == -1)
				fail_signal();
			client_pid = 0;
			index = 0;
			return ;
		}
		write(1, &decoded_char, 1);
		index = 0;
	}
	kill(client_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction signal_received;
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