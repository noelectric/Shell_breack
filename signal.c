#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
    
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void set_rl(char *input, char output, int fd, bool newline)
{
	if (input)
	{
		ft_putstr(input, fd);
		ft_putstr(": ", fd);
	}
	if (output)
		ft_putstr(output, fd);
	ft_putendl("", fd);
	if (newline)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (true);
}

void	signal_han(void (*action1)(int), void (*action2)(int))
{
	signal(SIGINT, action1);
	signal(SIGQUIT, action2);
}
void	custom(void)
{
	set_rl(NULL, NULL, STDOUT_FILENO, true);
}

int	main(void)
{
	signal_han(custom, SIG_IGN);
	return (0 ) ; 
}