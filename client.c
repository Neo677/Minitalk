/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:11:47 by thobenel          #+#    #+#             */
/*   Updated: 2024/09/07 18:11:49 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_receveid = 0;

static void	ft_counter(int num)
{
	static int	i;

	if (num == SIGUSR1)
	{
		g_ack_receveid = 1;
		ft_printf("numero = %d, message recu commandant\n", i);
		i++;
	}
}

static int	error_cheker(int ac)
{
	if (ac != 3)
		return (1);
	return (0);
}

static int	send_lengh(__pid_t server_pid, int len)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		g_ack_receveid = 0;
		if (len & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		while (!g_ack_receveid)
			usleep(50);
		len = len >> 1;
		i++;
	}
	return (0);
}

static int	send_message(__pid_t server_pid, char *msg, int delay)
{
	int	i;
	int	j;

	i = 0;
	while (msg[i])
	{
		j = 7;
		while (j >= 0)
		{
			g_ack_receveid = 0;
			usleep(delay);
			if (msg[i] & (1 << j))
				kill(server_pid, SIGUSR2);
			else
				kill(server_pid, SIGUSR1);
			while (!g_ack_receveid)
				usleep(delay);
			j--;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	__pid_t	server_pid;
	char	*message;
	int		len;
	int		delay;

	if (error_cheker(ac))
		return (ft_printf("Utilise PID = ***** || Message == *****\n"), 1);
	server_pid = ft_atoi(av[1]);
	if (server_pid == 0 || kill(server_pid, 0) == -1)
		return (ft_printf("Process with this id doesn't exist\n"), 1);
	message = av[2];
	len = ft_strlen(message);
	delay = 50;
	if (len > 12000)
		delay = 150;
	signal(SIGUSR1, ft_counter);
	send_lengh(server_pid, len);
	send_message(server_pid, message, delay);
	return (0);
}

/*static int	ft_send_count(__pid_t pid, int len)
{
	int	i;

	i = 0;
	while(i < 32)
	{
		if (len & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		len = len >> 1;
		usleep(50);
		i++;
	}
	return (0);
}

static int	ft_send_bits(int pid, char *str, int waiter)
{
	int	i;
	int	c;

	i = 0;
	while (str[i])
	{
		c = 7;
		while (c >= 0)
		{
			usleep(waiter);
			if (str[i] & (1 << c))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			c--;
		}
		i++;
	}
	return (0);
}

static int	handle_bad_enter(int ac)
{
	if (ac != 3)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int			len;
	int			waiter;
	char		*str;
	____pid_t	pid;

	if (handle_bad_enter(ac))
		return (ft_printf("God damn bro you cant even enter
			and id and a message ???\n seriously try again or you regret it\n"),
1);
	pid = ft_atoi(av[1]);
	if (pid == 0 || kill(pid, 0))
		return (printf("The ID is fake bro\n"), 1);
	str = av[2];
	len = ft_strlen(str);
	waiter = 50;
	if (len > 12000)
		waiter = 150;
	ft_send_count(pid, len);
	ft_send_bits(pid, str, waiter);
	return (0);
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

int	main(int ac, char **av)
{
	__pid_t		pid;
	const char	*str;
	int			i;

	i = 0;
	if (ac != 3)
	{
		ft_printf("utilise D'abord la PID = ******
			|| ton message == *****\n",
av[0]);
// 		exit(0);
// 	}
// 	pid = ft_atoi(av[1]);
// 	str = av[2];
// 	while (str[i] != '\0')
// 		ft_send_bits(pid, str[i++]);
// 	ft_send_bits(pid, '\0');
// 	return (0);
// }*/
