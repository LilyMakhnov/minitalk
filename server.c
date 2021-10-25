#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <sys/types.h> 

static void ft_putnbr(int a)
{
	char c;

	while (a > 9)
	{
		ft_putnbr(a / 10);
		a %= 10;
	}
	c = (char)a + '0';
	write(1, &c, 1);
}

static void	signal_handler(int signo, siginfo_t *info, void *context)
{
	static char byte_pos;
	static char byte;
	(void)context;

	if (signo == SIGUSR1)
		byte += 1 << (7 - byte_pos);
	byte_pos++;
	if (byte_pos == 8)
	{
		write(1, &byte, 1);
		byte_pos = 0;
		byte = 0;
	}
//	ft_putnbr(info->si_pid);
//	write(1, "\n", 1);
	if((int)info->si_pid != 0)
	{
		if(kill(info->si_pid, SIGUSR1) != 0)
			write(2, "ERROR PID CLIENT\n", 17);
	}
	else
		write(1, "ERROR\n", 6);
}

int main(int argc, char **argv) { 
	struct sigaction a; 

	(void)argv;
	a.sa_sigaction = &signal_handler;
	a.sa_flags = SA_SIGINFO;
	if (argc == 1)
	{
		if (sigaction(SIGUSR1, &a, NULL) != 0)
		{
			write(2, "ERROR\n", 7);
			return (0);
		}
		if (sigaction(SIGUSR2, &a, NULL) != 0)
		{
			write(2, "ERROR\n", 7);
			return (0);
		} 
		write(1, "SERVER PID: ", 12);
		ft_putnbr(getpid());
		write(1, "\n", 1);
		while(1)
			pause();
	}
	return (0); 
}
