/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:29:22 by elhovhan          #+#    #+#             */
/*   Updated: 2022/10/18 19:08:40 by elhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (str[i] - '0') + (result * 10);
		i++;
	}
	return (result * sign);
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1,"Message received",16);
		write(1, "\n", 1);
	}
}

int	main(int argc, char **argv)
{
	int	bit;
	int	i;
	struct sigaction sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_SIGINFO;
	if (argc == 3)
	{
		sigaction(SIGUSR1,&sa, NULL);
		while (*argv[2])
		{
			bit = 128;
			while (bit != 0)
			{
				if (*argv[2] & bit)
					kill(ft_atoi(argv[1]), SIGUSR1);
				else
					kill(ft_atoi(argv[1]), SIGUSR2);
				usleep(100);
				bit /= 2;
			}
			argv[2]++;
		}
		i = 8;
		while (i--)
		{
			kill(ft_atoi(argv[1]), SIGUSR2);
			usleep(100);
		}		
		return(0);
	}
	else
		return(1);
}
