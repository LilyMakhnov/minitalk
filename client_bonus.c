/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:57:15 by esivre            #+#    #+#             */
/*   Updated: 2021/10/27 16:55:14 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

static void	kill_error(int pid, int sig)
{
	if (sig == 1)
	{
		if (kill(pid, SIGUSR1) != 0)
		{
			write(2, "ERROR: WRONG PID\n", 17);
			exit(0);
		}
	}
	if (sig == 2)
	{
		if (kill(pid, SIGUSR2) != 0)
		{
			write(2, "ERROR: WRONG PID\n", 17);
			exit(0);
		}
	}
}

static int	send_char(int pid, char *str)
{
	static int	mask = 1 << 7;
	static int	pid_s = 0;
	static char	*message = 0;
	static int	nbr = 0;

	if (pid)
		pid_s = pid;
	if (str)
		message = ft_strdup(str);
	if (message[nbr] & mask)
		kill_error(pid_s, 1);
	else
		kill_error(pid_s, 2);
	mask >>= 1;
	if (!mask)
	{
		if (message[nbr++] == 0)
		{
			free(message);
			message = NULL;
			return (1);
		}
		mask = 1 << 7;
	}
	return (0);
}

static void	signal_handler(int signo)
{
	int	end;

	(void) signo;
	if (signo == SIGUSR1)
	{
		end = send_char(0, 0);
		if (end == 1)
			exit(0);
	}
	else
	{
		write(2, "ERROR SERVER\n", 13);
		exit(0);
	}
}

static char	check_number(char *nbr)
{
	while (*nbr)
	{
		if (*nbr > '9' || *nbr < '0')
			return (0);
		nbr++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int	pid;

	(void)argc;
	signal(SIGUSR1, signal_handler);
	if (argc == 3 && check_number(argv[1]))
	{
		pid = ft_atoi(argv[1]);
		if (pid == 0)
		{
			write(2, "ERROR: PID must be > 0\n", 23);
			return (0);
		}
		send_char(pid, argv[2]);
		while (1)
			pause();
	}
	else
		write(2, "ERROR: exe as ./client PID(number>0) string\n", 44);
	return (0);
}
