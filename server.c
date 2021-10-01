#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <sys/types.h> 

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
		if (byte == '\0')
			kill(info->si_pid, SIGUSR2);
		byte_pos = 0;
		byte = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

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

int main(void) { 
	struct sigaction a; 

	a.sa_sigaction = &signal_handler;
	a.sa_flags = SA_SIGINFO;
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
	return (0); 
}