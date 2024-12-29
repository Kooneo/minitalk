/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:04 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/29 17:54:31 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <sys/time.h>
#include <stdio.h>


char	bit_set[8];


static struct timeval start_time, end_time;


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
    {
		client_pid = info->si_pid;
        gettimeofday(&start_time, NULL);
    }
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
            gettimeofday(&end_time, NULL); // Record end time
			ft_printf("\nMessage received completely.\n");
            long seconds = end_time.tv_sec - start_time.tv_sec;
            long microseconds = end_time.tv_usec - start_time.tv_usec;
            double elapsed = seconds + microseconds * 1e-6;
            printf("Runtime: %.6f seconds\n", elapsed);
			kill(client_pid, SIGUSR1); // if (kill(???) == -1 write(2, "kill error", len))
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

	int i = 0;
	while (i < 8)
		bit_set[i++] = '0';
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}