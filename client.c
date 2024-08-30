/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomtom <tomtom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:06:56 by thobenel          #+#    #+#             */
/*   Updated: 2024/08/29 20:21:41 by tomtom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void	ft_send_bits(int pid, char *str)
{
	int		bits;
	char	carac;

	while (*str)
	{
		bits = 8;
		carac = *str++;
		while(bits--)
		{
			if (carac >> bits & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
	}
}

static void	send_count(int signal)
{
	static int	get;

	get = 0;
	if (signal == SIGUSR1)
		++get;
	else
	{
		ft_putnbr_fd(get, 1);
		ft_pustchar_fd('\n', 1);
		exit (0);
	}
}

int main(int ac, char **av)
{
	if (ac !=  3 || !ft_strlen(av[2]))
		return (1);
	ft_puststr_fd("sent ...	:", 1);
	ft_putnbr_fd(ft_strlen(av[2]), 1);
	ft_pustchar_fd('\n', 1);
	ft_puststr_fd("Receveid: ", 1);
	signal(SIGUSR1, send_count);
	signal(SIGUSR2, send_count);
	ft_send_bits(ft_atoi(av[1]), av[2]);
	while(1)
		pause();
	return(0);
}

// int	main(int ac, char **av)
// {
// 	pid_t		pid;
// 	const char	*str;
// 	int			i;

// 	i = 0;
// 	if (ac != 3)
// 	{
// 		ft_printf("utilise D'abord la PID = ****** || ton message == *****\n", av[0]);
// 		exit(0);
// 	}
// 	pid = ft_atoi(av[1]);
// 	str = av[2];
// 	while (str[i] != '\0')
// 		ft_send_bits(pid, str[i++]);
// 	ft_send_bits(pid, '\0');
// 	return (0);
// }