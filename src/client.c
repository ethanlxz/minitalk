/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:30:22 by etlaw             #+#    #+#             */
/*   Updated: 2023/02/04 13:32:13 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include <stdio.h>
#include <stdlib.h>

void	send_signal(int pid, char a)
{
	int	bits;

	bits = 0;
	while (bits < 8)
	{
		if (a & (0x01 << bits) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bits++;
	}
}

// change back atoi and printf 
// change back libriary both client and server

int	main(int ac , char **av)
{
	int	pid;
	int	i;

	i = 0;
	if (ac == 3)
	{
		pid = atoi(av[1]);
		while (av[2][i] != '\0')
		{
			send_signal(pid, av[2][i]);
			i++;
		}
		send_signal(pid, '\n');	
	}
	else
	{
		printf("\033[91mWoops! Wrong format!\033[0m\n");
		printf("\033[33mTry: ./client_bonus [PID] [MESSAGE]\033[0m\n");
		return (0);
	}
	return (0);
}
