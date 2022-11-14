#include "../include/minishell.h"

void	new_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	back_slash(int sig)
{
	printf("Quit\n");
	(void)sig;
}

void sign_handler(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, new_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		printf("exit\n");
		exit(0);
	}
	
}

int main(int argc, char const *argv[], char *envp[])
{
	t_env	*envmap;
	t_lst	*chunks;
	t_as	*syntax;
	char	*input;

	(void)argc;
	(void)argv;
	envmap = envirement(envp);
	signal(SIG_INT, sign_handler);
	// rl_catch_signals = 0;
	loop(input, chunks, syntax, envmap);
	return 0;
}
