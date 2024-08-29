/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomtom <tomtom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:26:45 by thobenel          #+#    #+#             */
/*   Updated: 2024/08/29 19:32:14 by tomtom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	ft_putchar_fd(char c, int fd);
char	ft_putstr(char *str);
char	ft_putstr_fd(char *str, int fd);
int ft_putnbr_fd(int nb, int fd);
int	ft_strlen(char *str);



#endif