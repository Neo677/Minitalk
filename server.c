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

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define FIN_TRANSMISSION '\0'

int	ft_strlen(char *str)
{
	int i;
	i = 0;
	while(str[i])
		i++;
	return (i);
}

char	strrev(char *str)
{
	char *dbt;
	char *end;
	char temp;

	dbt = str;
	end = str + ft_strlen(str) - 1;
	while(dbt < end)
	{
		temp = *dbt;
		*dbt = *end;
		*end = temp;
		dbt++;
		end--;
	}
	return (*str);
}

void	ft_handle(int sig)
{
	static unsigned char	str;
	static int				i;

	str |= (sig == SIGUSR1);
	// str = ft_itoa(str |= (sig == SIGUSR1));
	i++;
	if (i == 8)
	{
		if (str == FIN_TRANSMISSION)
			ft_printf("\n");
		else
			ft_printf("%c", str);
		i = 0;
		str = 0;
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
	ft_baniere();
	ft_pid();
	signal(SIGUSR1, ft_handle);
	signal(SIGUSR2, ft_handle);
	ft_printf("*------------------------------------------*\n");
	ft_printf("|            Waiting for message...        |\n");
	ft_printf("|                                          |\n");
	ft_printf("|                                          |\n");
	while (1)
		pause();
	return (0);
}