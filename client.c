/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:01:33 by thobenel          #+#    #+#             */
/*   Updated: 2024/08/16 10:01:36 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

# include "printf/ft_printf.h"

void	ft_send_bits(int pid, char i)
{
	int	bits;

	bits = 0;
	while (bits < 8)
	{
		if ((i & (0x01 << bits)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bits++;
	}
}

static int	ft_atoi(const char *str)
{
	unsigned long long	nb;
	int					i;
	int					neg;

	i = 0;
	neg = 1;
	nb = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && (str[i]))
	{
		nb = (nb * 10) + (str[i] - '0');
		if ((nb > 9223372036854775807) && neg == 1)
			return (-1);
		if ((nb > 9223372036854775807) && neg == -1)
			return (0);
		i++;
	}
	return (nb * neg);
}

int main(int ac, char **av)
{
	__pid_t server_pid;
	int i;
	const char *message;

	if (ac != 3)
	{
		ft_printf("Usage: %s <pid> <message>\n", av[0]);
		exit(0);
	}
	server_pid = ft_atoi(av[1]);
	message = av[2];
	i = 0;
	while (message[i])
		ft_send_bits(server_pid, message[i++]);
	ft_send_bits(server_pid, '\0');
	return (0);
}
