//			header

#include "minitalk.h"

void	ft_send_bits(int pid, char i)
{
	int 	bits;

	bits = 0;
	while(bits < 8)
	{
		if ((i & (0x01 << bits)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bits++;
	}
}

static int ft_atoi(const char *str)
{
	unsigned long long nb;
	int i;
	int neg;

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

int	main(int ac, char **av)
{
	int pid;
	int i;

	i = 0;
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		while(av[2][i] != '\0')
		{
			ft_send_bits(pid, av[2][i]);
			i++;
		}
		ft_send_bits(pid, '\n');
	}
	else
	{
		ft_printf("");
		ft_printf("");
		return (1);
	}
	return (0);
}