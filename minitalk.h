/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:26:45 by thobenel          #+#    #+#             */
/*   Updated: 2024/08/28 13:26:47 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

typedef struct mini_data
{
	int			x;
	char		y;
	int			pid;
}		mini_dato;

char	ft_putstr(char *str);
int	ft_atoi(const char *str);
char	ft_itoa(unsigned int i);


#endif