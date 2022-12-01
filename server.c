/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:30:25 by chchin            #+#    #+#             */
/*   Updated: 2022/06/09 15:09:25 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_sigaction(int signo, siginfo_t *sa_siginfo, void *ucontext)
{
	static int	i;
	static char	c;
	int			bit;

	(void)(*ucontext);
	if (signo == SIGUSR1)
		bit = 1;
	else
		bit = 0;
	c += bit;
	if (++i == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill(sa_siginfo->si_pid, SIGUSR1);
		}
		i = 0;
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("Server PID: %d\n", getpid());
//	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &sig_sigaction;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
