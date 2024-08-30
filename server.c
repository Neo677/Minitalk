/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomtom <tomtom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:07:07 by thobenel          #+#    #+#             */
/*   Updated: 2024/08/23 21:36:08 by tomtom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


static void	ft_tyesfada(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_handle(int sig, siginfo_t *info, void *txt)
{
	static unsigned char	str;
	static int				i;
	static __pid_t			pid;

	(void)txt;
	i = 0;
	pid = 0;
	str = 0;
	if (!pid)
		pid = info->si_pid;
	str |= (sig == SIGUSR2);
	i++;
	if (i == 8)
	{
		i = 0;
		if (!str)
		{
			kill(pid, SIGUSR2);
			pid = 0;
			return ;
		}
		ft_tyesfada(str, 1);
		str = 0;
		kill(pid, SIGUSR1);
	}
	else
		str <<= 1;
}

void	ft_baniere(void)
{
	ft_printf("*------------------------------------------*\n");
	ft_printf("|                                          |\n");
	ft_printf("|            Welcome to MiniTalk           |\n");
	ft_printf("|                                          |\n");
	ft_printf("*------------------------------------------*\n");
	ft_printf("\n\n");
}

void	ft_pid(void)
{
	ft_printf("*------------------------------------------*\n");
	ft_printf("|            Serveur PID: %d           |\n", getpid());
	ft_printf("*------------------------------------------*\n");
	ft_printf("\n\n");
}

int	main(void)
{
	struct sigaction s_sigaction;

	ft_baniere();
	ft_pid();
	s_sigaction.sa_sigaction = ft_handle;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	ft_printf("*------------------------------------------*\n");
	ft_printf("|            Waiting for message...        |\n");
	ft_printf("|                                          |\n");
	ft_printf("|                                          |\n");
	while (1)
		pause();
	return (0);
}