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

static int	read_len_bit(int signo, int len)
{
	len = len >> 1;
	if (signo == SIGUSR2)
		len = len | (1 << 30);
	return (len);
}

static char	*malloc_message(int len)
{
	char	*res;

	res = (char *)malloc((len + 1) * sizeof(char));
	ft_bzero(res, len);
	if (!res)
		return (NULL);
	res[len] = '\0';
	return (res);
}

static void	finalise(char **res, __pid_t client_pid, int *len, int *i)
{
	ft_printf("%s\n", *res);
	usleep(51);
	kill(client_pid, SIGUSR1);
	free(*res);
	*res = NULL;
	*len = 0;
	*i = 0;
}

static void	signal_handler(int signo, siginfo_t *info, void *context)
{
	static int	len = 0;
	static int	i = 0;
	static char	*res;

	if (i < 31)
		len = read_len_bit(signo, len);
	else if (i < 32)
	{
		res = malloc_message(len);
		if (!res)
		{
			ft_putstr_fd("ERROR: memory allocation failed\n", 2);
			exit(1);
		}
	}
	else if (i <= len * 8 + 32 && signo == SIGUSR2)
			res[(i - 32) / 8] |= (1 << (7 - (i - 32) % 8));
	i++;
	if (i == len * 8 + 32)
		finalise(&res, info->si_pid, &len, &i);
	(void)context;
}

int	main(void)
{
	__pid_t				pid;
	struct sigaction	action;

	pid = getpid();
	ft_printf("Server process id: %i\n", pid);
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
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
// 	else if (bits_treated <= len * 8 + 32 && signal == SIGUSR2)
// 		ptr_message[(bits_treated - 32) / 8] |= (1 << (7 - (bits_treated - 32) % 8));
// 	bits_treated++;
// 	if (bits_treated == len * 8 + 32)
// 		show_up(&ptr_message, info->si_pid, &len, &bits_treated);
// 	(void)txt;
// }


// int	main(void)
// {
// 	struct sigaction	s_action;
// 	__pid_t	pid;
	
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

