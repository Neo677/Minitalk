/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomtom <tomtom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:15:54 by thobenel          #+#    #+#             */
/*   Updated: 2024/09/05 23:24:15 by tomtom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_get_len|bit(int signal, int len)
{
	len = len >> 1;
	if (signal == SIGUSR2)
		len = len | (1 << 30);
	return (len)
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = ft_handle;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}

// void	ft_baniere(void)
// {
// 	ft_putstr_fd("*------------------------------------------*\n", 1);
// 	ft_putstr_fd("|                                          |\n", 1);
// 	ft_putstr_fd("|            Welcome to MiniTalk           |\n", 1);
// 	ft_putstr_fd("|                                          |\n", 1);
// 	ft_putstr_fd("*------------------------------------------*\n", 1);
// 	ft_putstr_fd("\n", 1);
// }

// // ft_putstr_fd("*------------------------------------------*\n", 1);
// // ft_putstr_fd("|            Serveur PID: &i           |\n", i);
// // ft_putstr_fd("*------------------------------------------*\n", 1);

// int	main(void)
// {
// 	struct sigaction	sa;

// 	ft_baniere();
// 	ft_putstr_fd("		Your PID: ", 1);
// 	ft_putnbr_fd(getpid(), 1);
// 	sa.sa_sigaction = ft_handle;
// 	sa.sa_flags = SA_SIGINFO;
// 	sigaction(SIGUSR1, &sa, 0);
// 	sigaction(SIGUSR2, &sa, 0);
// 	ft_putstr_fd("*------------------------------------------*\n", 1);
// 	ft_putstr_fd("|            Waiting for message...        |\n", 1);
// 	ft_putstr_fd("|                                          |\n", 1);
// 	ft_putstr_fd("|                                          |\n", 1);
// 	while (1)
// 		pause();
// 	return (0);
// }

//static void	ft_handle(int signal, siginfo_t *info, void *txt)
// {
// 	static int				bits = 0;
// 	static pid_t			pid = 0;
// 	static unsigned char	carac = 0;

// 	if (!pid)
// 		pid = info->si_pid;
// 	carac |= (signal == SIGUSR2);
// 	if (++bits == 8)
// 	{
// 		bits = 0;
// 		if (!carac)
// 		{
// 			kill(pid, SIGUSR2);
// 			pid = 0;
// 			return ;
// 		}
// 		ft_putchar_fd(carac, 1);
// 		carac = 0;
// 		kill(pid, SIGUSR1);
// 	}
// 	else
// 		carac <<= 1;
// }