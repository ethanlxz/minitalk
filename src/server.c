/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:28:45 by etlaw             #+#    #+#             */
/*   Updated: 2023/05/29 20:15:33 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	reciever(int signal, siginfo_t *info, void *s)
{
	static char	c;
	static int	bits;

	(void)s;
	if (signal == SIGUSR1)
		c += (0x01 << bits);
	bits++;
	if (bits == 8)
	{
		ft_printf("%c", c);
		bits = 0;
		if (c == '\n')
			kill(info->si_pid, SIGUSR2);
		c = 0;
	}
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sig;

	(void)av;
	pid = getpid();
	if (ac != 1)
	{
		ft_printf("\033[0;31mOops! :( Wrong format!\n");
		ft_printf("Try ./server\n\033[0m");
		return (0);
	}
	ft_printf("\033[0;31mInitializing server...\n\033[0m");
	sleep(1);
	ft_printf("\033[0;32mPID is %d\n\n\033[0m", pid);
	sleep(1);
	ft_printf("\033[0;32mWaiting for signals :)\n\n\033[0m");
	sig.sa_sigaction = reciever;
	while (ac == 1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause ();
	}
	return (0);
}
