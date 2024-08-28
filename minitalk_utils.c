/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:14:37 by thobenel          #+#    #+#             */
/*   Updated: 2024/08/28 13:14:39 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

char	ft_putstr(char *str)
{
	int 	i;

	i = 0;
	while(str[i])
		write(1, str[i++], 1);
	return (str);
}

int	ft_atoi(const char *str)
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

char	ft_itoa(unsigned int i)
{
	char *str;
	int j;

	j = 0;
	str = (char *)malloc(sizeof(char));
	if (!str)
		return (free(str), 0);
	str[j] = '\0';
	while(i > 0)
	{
		str[j] = (i % 10) + '0';
		i /= 10;
		j++;
	}
	if (j == 0)
		str[j++] = '0';
	return (strrev(str));
}