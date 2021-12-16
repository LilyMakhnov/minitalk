/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:00:14 by esivre            #+#    #+#             */
/*   Updated: 2021/10/27 16:46:50 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h> 
#include "libft/libft.h"

static void	ft_putnbr(int a)
{
	char	c;

	while (a > 9)
	{
		ft_putnbr(a / 10);
		a %= 10;
	}
	c = (char)a + '0';
	write(1, &c, 1);
}

static void	error_server(int pid)
{
	write(2, "ERROR SERVER\n", 14);
	if (pid > 0)
		kill(pid, SIGUSR2);
	exit(0);
}

static void	signal_handler(int signo, siginfo_t *info, void *context)
{
	static char	byte_pos = 0;
	static char	byte = 0;
	static char	*message = 0;

	(void)context;
	if (signo == SIGUSR1)
		byte += 1 << (7 - byte_pos);
	byte_pos++;
	if (byte_pos == 8)
	{
		byte_pos = 0;
		if (byte)
			message = ft_straddchar(message, byte);
		else
		{
			ft_putstr_fd(message, 1);
			free(message);
			message = NULL;
			return ;
		}
		byte = 0;
	}
	if (kill(info->si_pid, SIGUSR1) != 0)
		error_server(info->si_pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	a;

	(void)argv;
	if (argc == 1)
	{
		a.sa_sigaction = &signal_handler;
		a.sa_flags = SA_SIGINFO;
		if (sigaction(SIGUSR1, &a, NULL) != 0)
			error_server(0);
		if (sigaction(SIGUSR2, &a, NULL) != 0)
			error_server(0);
		write(1, "SERVER PID: ", 12);
		ft_putnbr(getpid());
		write(1, "\n", 1);
		while (1)
			pause();
	}
	else
		write(2, "ERROR: no arguments needed\n", 27);
	return (0);
}
