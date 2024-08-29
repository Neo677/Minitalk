/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomtom <tomtom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:06:56 by thobenel          #+#    #+#             */
/*   Updated: 2024/08/23 21:33:30 by tomtom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void	ft_send_bits(int pid, char *str)
{
	int		bits;
	char	carac;

	bits = 8;
	while (*str)
	{
		carac = *str++;
		while(bits--)
		{
			if (carac >> 2 == 0)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(42);
		}
	}
}

static void	send_count(int signal)
{
	int	get;

	get = 0;
	if (signal == SIGUSR1)
		get++;
	else
	{
		ft_putnbr_fd(get, 1);
		ft_putchar_fd('\n', 1);
		exit (0);
	}
}


int	main(int ac, char **av)
{
	pid_t		pid;
	const char	*str;
	int			i;

	i = 0;
	if (ac != 3)
	{
		ft_printf("utilise D'abord la PID = ****** || ton message == *****\n", av[0]);
		exit(0);
	}
	pid = ft_atoi(av[1]);
	str = av[2];
	while (str[i] != '\0')
		ft_send_bits(pid, str[i++]);
	ft_send_bits(pid, '\0');
	return (0);
}