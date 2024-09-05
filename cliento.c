/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cliento.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomtom <tomtom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:15:54 by thobenel          #+#    #+#             */
/*   Updated: 2024/09/05 23:25:26 by tomtom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	input_invalid(int ac)
{
	if (ac != 3)
		return (1);
	return (0);
}

static int	send_len(pid_t server_pid, int len)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (len & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		len = len >> 1;
		usleep(50);
		i++;
	}
	return (0);
}

static int	send_msg(pid_t server_pid, char *msg, int delay)
{
	int	i;
	int	j;

	i = 0;
	while (msg[i])
	{
		j = 7;
		while (j >= 0)
		{
			usleep(delay);
			if (msg[i] & (1 << j))
				kill(server_pid, SIGUSR2);
			else
				kill(server_pid, SIGUSR1);
			j--;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char	**av)
{
	pid_t	server_pid;
	char	*message;
	int		len;
	int		delay;

	if (input_invalid(ac))
	{
		ft_printf("Please provide server process id and your message\n");
		return (1);
	}
	server_pid = ft_atoi(av[1]);
	if (server_pid == 0 || kill(server_pid, 0))
	{
		ft_printf("Process with this id doesn't exist\n");
		return (1);
	}
	message = av[2];
	len = ft_strlen(message);
	delay = 50;
	if (len > 12000)
		delay = 150;
	send_len(server_pid, len);
	send_msg(server_pid, message, delay);
	return (0);
}
