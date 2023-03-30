/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:16:36 by elhovhan          #+#    #+#             */
/*   Updated: 2022/10/18 19:02:21 by elhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void	ft_putnbr(int n)
{
	long	b;
	char	c;

	b = n;
	if (b < 0)
	{
		write(1, "-", 1);
		b = b * (-1);
	}
	if (b > 9)
	{
		ft_putnbr(b / 10);
		ft_putnbr(b % 10);
	}
	else
	{
		c = b + 48;
		write(1, &c, 1);
	}
}

void	handler(int sig, siginfo_t *info, void *a)
{
	static unsigned char	c = 0;
	static int				flag = 0;
   	static pid_t			client_pid = 0;

	(void)a;
	if (!client_pid)
   		client_pid = info -> si_pid;
	++flag;
	c *= 2;
	if (sig == SIGUSR1)
		c = c | 1;
	if (flag == 8)
	{	
		write(1, &c, 1);
		flag = 0;
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill(client_pid, SIGUSR1);
			client_pid = 0;
		}
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sig;
	
	sig.sa_sigaction = handler;
	sig.sa_flags = SA_SIGINFO;
	pid = getpid();
	write(1, "Server PID is ", 14);
	ft_putnbr(pid);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1);
}
