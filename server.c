/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:23:23 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/02 13:23:25 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_signal_receveid = 0;

static int	bit_len(int signo, int len)
{
	len = len >> 1;
	if (signo == SIGUSR2)
		len = len | (1 << 30);
	return (len);
}

static char	*message_allocation(int len)
{
	char	*res;

	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (free(res), NULL);
	ft_bzero(res, len + 1);
	res[len] = '\0';
	return (res);
}

static void	finish_it_bro(char **res, pid_t client_pid, int *len, int *i)
{
	ft_printf("%s\n", *res);
	usleep(51);
	kill(client_pid, SIGUSR1);
	free(*res);
	*res = NULL;
	*len = 0;
	*i = 0;
}

static void	get_this_signal(int signo, siginfo_t *info, void *context)
{
	static int	len = 0;
	static int	i = 0;
	static char	*res = NULL;
	pid_t		pid;

	pid = info->si_pid;
	if (i < 31)
		len = bit_len(signo, len);
	else if (i < 32)
	{
		res = message_allocation(len);
		if (!res)
			exit(0);
	}
	else if (i <= len * 8 + 32 && signo == SIGUSR2)
		res[(i - 32) / 8] |= (1 << (7 - (i - 32) % 8));
	i++;
	if (i == len * 8 + 32)
		finish_it_bro(&res, pid, &len, &i);
	g_signal_receveid = 1;
	kill(pid, SIGUSR1);
	(void)context;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;

	pid = getpid();
	ft_printf("*------------------------------------------*\n", 1);
	ft_printf("|                                          |\n", 1);
	ft_printf("|            Welcome to MiniTalk           |\n", 1);
	ft_printf("|                                          |\n", 1);
	ft_printf("*------------------------------------------*\n", 1);
	ft_printf("*------------------------------------------*\n", 1);
	ft_printf("|            Serveur PID: %i          |\n", pid);
	ft_printf("*------------------------------------------*\n", 1);
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = get_this_signal;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
	{
		pause();
		while (!g_signal_receveid)
			usleep(50);
		g_signal_receveid = 0;
	}
	return (0);
}

// static int ft_get_len_bit(int signal, int len)
// {
// 	len = len >> 1;
// 	if (signal == SIGUSR2)
// 		len = len | (1 << 30);
// 	return (len);
// }

// static void	show_up(char **rslt, __pid_t pid, int *len, int *i)
// {
// 	ft_printf("%s\n", *rslt);
// 	usleep(51);
// 	kill(pid, SIGUSR1);
// 	free(*rslt);
// 	*rslt = NULL;
// 	*len = 0;
// 	*i = 0;
// }

// static char	*ft_memory_of_str(int len)
// {
// 	char *res;

// 	res = (char *)malloc((len + 1) * sizeof(char));
// 	ft_bzero(res, len);
// 	if (!res)
// 		return (free(res), NULL);
// 	res[len] = '\0';
// 	return (res);
// }

// static void	ft_handle(int signal, siginfo_t *info, void *txt)
// {
// 	static int				len = 0;
// 	static int	bits_treated = 0;
// 	static char	*ptr_message;

// 	if (bits_treated < 31) // read bit by bit
// 		len = ft_get_len_bit(signal, len);
// 	else if (bits_treated < 32)
// 	{
// 		ptr_message = ft_memory_of_str(len);
// 		if (!ptr_message)
// 		{
// 			ft_printf("malloc failled");
// 			exit(1);
// 		}
// 	}
// 	bits_treated++;
// 	if (bits_treated == len * 8 + 32)
// 		show_up(&ptr_message, info->si_pid, &len, &bits_treated);
// 	(void)txt;
// }

// int	main(void)
// {
// 	struct sigaction	s_action;
// 	____pid_t	pid;

// 	pid = getpid();
// 	ft_printf("The ID is : %i\n", pid);
// 	sigemptyset(&s_action.sa_mask);
// 	s_action.sa_flags = SA_SIGINFO;
// 	s_action.sa_sigaction = ft_handle;
// 	sigaction(SIGUSR1, &s_action, NULL);
// 	sigaction(SIGUSR2, &s_action, NULL);
// 	while (1)
// 		pause();
// 	return (0);
// }

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
