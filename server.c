/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:01:41 by thobenel          #+#    #+#             */
/*   Updated: 2024/08/16 10:01:43 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "printf/ft_printf.h"
#define FIN_TRANSMISSION '\0'

void	ft_handle(int sig)
{
	static unsigned char str;
	static int i;

	str |= (sig == SIGUSR1);
	i++;
	if (i == 8)
	{
		if (str == FIN_TRANSMISSION)
			ft_printf("\n");
		else
			ft_printf("%c", str);
		i = 0;
	}
	else
		str <<=1;
}

int main(void)
{
	ft_printf("Your pid = %d\n", getpid);
	signal(SIGUSR1, ft_handle);
	signal(SIGUSR2, ft_handle);
	while(1)
		pause;
	return (0);
}