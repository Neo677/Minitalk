/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:23:17 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/02 13:23:19 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_receveid = 0;
// Acknowledgment (accusé de réception)

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
//			lorsque le SIGUSR1 est recu alors on incr une var i
//			et print la valeur du signal recu

static int	error_cheker(int ac)
{
	if (ac != 3)
		return (1);
	return (0);
}

//		check le nb arg est bien 3

static int	send_lengh(pid_t server_pid, int len)
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

// envoie la longueur du message (len) au serveur, bit par bit.
// utilise un entier de 32 bits pour encoder la longueur et envoie chaque bit
// en utilisant des signaux SIGUSR1 (pour le bit 0) et SIGUSR2 (pour le bit 1).
// attend un accusé de réception (ACK) entre chaque envoi.

static int	send_message(pid_t server_pid, char *msg, int delay)
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

/*  Cette fonction envoie chaque caractère du message au serveur, bit par bit.
utilise SIGUSR1 pour envoyer un bit de valeur 0 
et SIGUSR2 pour un bit de valeur 1.
   Un accusé de réception (ACK) est attendu après l'envoi de chaque bit.
*/

int	main(int ac, char **av)
{
	pid_t	server_pid;
	char	*message;
	int		len;
	int		delay;

	if (error_cheker(ac))
		return (ft_printf("Utilise ton PID = ***** et ton Message == *****\n"),
			1);
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

/*
int	main(int ac, char **av)
{
	pid_t	server_pid;
	char	*message;
	int		len;
	int		delay;

	if (error_cheker(ac))
		return (ft_printf("Utilise ton PID = ***** et ton Message == *****\n"),
			1);
		// check le bon fonctionement des args
	server_pid = ft_atoi(av[1]);
		// convertie le pid en entier
	if (server_pid == 0 || kill(server_pid, 0) == -1)
		return (ft_printf("Process with this id doesn't exist\n"), 1);
		// check si le pid est correct
	message = av[2];
		// stock le message
	len = ft_strlen(message);
		//stock sa longueur
	delay = 50;
		// cree un delai pour son envoie
	if (len > 12000)
		delay = 150;
		// si le delaie est
			+ grand alors on augmente en moyenne la longueur est de 10.000
	signal(SIGUSR1, ft_counter);
		// Attache SIGUSR1 à la fonction ft_counter pour gérer les Acknowledgment
	send_lengh(server_pid, len);
		// envoie la longeur du message
	send_message(server_pid, message, delay);
		// envoie le message
	return (0);
}
*/

/*static int	ft_send_count(pid_t pid, int len)
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
	pid_t		pid;
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
