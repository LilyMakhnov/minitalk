#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int	ft_atoi(const char *nbr)
{
	int res; 
	int sign:

	res = 0;
	sign = 1;
	while (*nbr == ' ' || (*nbr >= 9 && *nbr <= 13))
		nbr++;
	if (*nbr == '+' || *nbr == '-')
		if (*nbr++ == '-')
			sign *= -1;
	while (ft_isdigit(*nbr))
		res = res * 10 + *nbr++ - '0';
	return (sign * res);
}

static int	send_char(int pid, char a)
{
	int mask;

	mask = 1 << 7;
	while (mask)
	{
		if (a & mask)
		{
			if (kill(pid, SIGUSR1) != 0)
			{
				write(2, "ERROR PID SIG1\n", 15);
				return (-1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) != 0)
			{
				write(2, "Error PID SIG2\n", 15);
				return (-1);
			}
		}
		mask >>= 1;
		usleep(200);
	}
	return (0);
}

void signal_handler(int signo)
{
	(void) signo;
}

void end(int signo)
{
	(void)signo;
	write(1, "MESSAGE SENDED AND RECEVED BY SERVER\n", 37);
}

int main(int argc, char **argv)
{
	(void)argc;
	int i;
	int pid;

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, end);
	if (argc != 3)
		return (0);
	i = 0;
	while (argv[2][i])
	{
		pid = ft_atoi(argv[1]);
		if (send_char(pid, argv[2][i++]) == -1)
			break;
	}
	send_char(pid, '\0');
	usleep(1000);
	return (0);
}
