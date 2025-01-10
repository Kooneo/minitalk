/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:20:25 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/09 22:46:44 by zbakour          ###   ########.fr       */
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
	size_t i;

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
	else if (signum == SIGUSR1)
		ft_printf("\n✅ Message sent and received successfully!\n");
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc == 3)
	{
		signal(SIGUSR2, signal_handler);
		signal(SIGUSR1, signal_handler);
		pid = ft_atoi(argv[1]);
		if (pid < 0)
			show_error("⛔ PID Can't be Negative Value.");
		message = argv[2];
		if (pid < 0 || message[0] == '\0')
			return (1);
		message_encryption(message, pid);
	}
	else
		show_error("🚀 Usage: <PID> <MESSAGE>");
	return (0);
}
