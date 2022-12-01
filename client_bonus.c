/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 09:04:08 by chchin            #+#    #+#             */
/*   Updated: 2022/06/10 09:04:08 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_error(pid_t pid)
{
	ft_printf("Server PID %d not found\n", pid);
	exit(0);
}

void	reverse_bits(pid_t pid, char c)
{
	unsigned int	byte_len;

	byte_len = 8;
	while (byte_len--)
	{
		if (c >> byte_len & 1)
		{
			if (kill(pid, SIGUSR1) < 0)
				sig_error(pid);
		}
		else
		{
			if (kill(pid, SIGUSR2) < 0)
				sig_error(pid);
		}
		usleep(50);
	}
}

void	send_msg(pid_t pid, char *str)
{
	while (*str)
		reverse_bits(pid, *str++);
	reverse_bits(pid, *str);
}

void	handler(int signu)
{
	if (signu == SIGUSR1)
		ft_printf("Server: Message received successfully.\n");
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	char				*msg;

	if (argc != 3)
	{
		ft_printf("Usage:%s <PID_Server> <Message>\n", argv[0]);
		return (0);
	}
	if (argv[2][0] == '\0')
	{
		ft_printf("Empty message is not allowed\n");
		return (0);
	}
	ft_printf("Message sent.\n");
	sleep(3);
	signal(SIGUSR1, handler);
	pid = ft_atoi(argv[1]);
	msg = argv[2];
	send_msg(pid, msg);
}
