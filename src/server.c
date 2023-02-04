/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:28:45 by etlaw             #+#    #+#             */
/*   Updated: 2023/02/04 14:04:55 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include <stdio.h>

void	reciever(int signal)
{
	static char c;
	static int bits;

	if (signal == SIGUSR1)
		c |= (0x01 << bits);
	bits++;
	if (bits == 8)
	{
		printf("%c", c);
		bits = 0;
		c = 0;
	}
}

int	main(int ac, char **av)
{
	int	pid;

	(void)av;
	pid = getpid();
	if (ac != 1)
	{
		printf("\033[0;31mOops! :( Wrong format!\n");
		printf("Try ./server\n\033[0m");
		return (0);
	}
	printf("\033[0;31mInitializing server...\n\033[0m");
	sleep(1);
	printf("\033[0;32mPID is %d\n\n\033[0m", pid);
	sleep(1);
	printf("\033[0;32mWaiting for signals :)\n\n\033[0m");
	while (ac == 1);
	{
		signal(SIGUSR1, reciever);
		signal(SIGUSR2, reciever);
		pause ();
	}
	return (0);
}
