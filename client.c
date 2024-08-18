/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomtom <tomtom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:01:33 by thobenel          #+#    #+#             */
/*   Updated: 2024/08/18 12:00:32 by tomtom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_send_bits(int pid, unsigned char str)
{
	int				bits;
	unsigned char	carac;

	bits = 8;
	carac = str;
	while (bits > 0)
	{
		bits--;
		carac = str >> bits;
		if (carac % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(42);
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
		i++;
	}
	return (nb * neg);
}

int	main(int ac, char **av)
{
	pid_t		pid;
	const char	*str;
	int			i;

	if (ac != 3)
	{
		ft_printf("use %s <pid> <message>\n", av[0]);
		exit(0);
	}
	pid = ft_atoi(av[1]);
	str = av[2];
	i = 0;
	while (str[i])
		ft_send_bits(pid, str[i++]);
	ft_send_bits(pid, '\0');
	return (0);
}
