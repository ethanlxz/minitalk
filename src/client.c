/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:30:22 by etlaw             #+#    #+#             */
/*   Updated: 2023/05/29 20:32:47 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	confirm(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("\033[0;32mRecieved!\033[0;32m\n", 1);
}

void	send_signal(int pid, char a)
{
	int	bits;

	bits = 0;
	while (bits < 8)
	{
		if ((a & (0x01 << bits)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bits++;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	i = 0;
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (av[2][i] == '\0')
		{
			send_signal(pid, '\n');
			signal(SIGUSR2, confirm);
			pause();
			return (0);
		}
		while (av[2][i] != '\0')
		{
			// signal(SIGUSR2, confirm);
			signal(SIGUSR2, confirm);
			send_signal(pid, av[2][i]);
			i++;
		}
		send_signal(pid, '\n');
	}
	else
	{
		ft_printf("\033[91mWoops! Wrong format!\033[0m\n");
		ft_printf("\033[33mTry: ./client_bonus [PID] [MESSAGE]\033[0m\n");
		return (0);
	}
	return (0);
}
