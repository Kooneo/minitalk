/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:41:55 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/28 18:41:57 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	signal_handler(int signum)
{
	printf("Received signal %d\n", signum);
}

int	main(void)
{
	struct sigaction action;
	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	sigaction(SIGINT, &action, NULL);

	while (1)
	{
		// Do some work
	}

	return (0);
}