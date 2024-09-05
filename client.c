/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomtom <tomtom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:15:37 by thobenel          #+#    #+#             */
/*   Updated: 2024/09/01 00:17:44 by tomtom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void	ft_send_count(int signal)
{
	static int	received;
	
	received = 0;

	if (signal == SIGUSR1)
		++received;
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

static void	ft_send_bits(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	ft_putstr_fd("Sent    : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	signal(SIGUSR1, ft_send_count);
	signal(SIGUSR2, ft_send_count);
	ft_send_bits(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
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
