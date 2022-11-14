#include "../include/minishell.h"

bool    quotes(char *input)
{
    while (*input)
    {
        if (*input == '\"')
            input = ft_strchr(input + 1, '\"');
        if (*input == NULL)
            return (false);
        if (*input == '\'')
            input = ft_strchr(input + 1, '\'');
        if (*input == NULL)
            return (false);
        input++;
    }
    return (true);
}

bool   set_rl(char *input, char *output, int fd, bool nl)
{
    if (input != NULL)
	{
		ft_putstr(input, fd);
		ft_putstr(": ", fd);
	}
	if (output != NULL)
		ft_putstr(output, fd);
	ft_putendl("", fd);
	if (nl)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (true);
} 

void    loop(char *input, t_lst *chunks, t_as *syntax, t_lst *envmap)
{
    while (1)
    {
        ft_free((void **)&input);
        input = readline("SHELL_BREACK > ");
        if (!input)
        {
            ft_putendl("exit", STDOUT_FILENO);
            exit(0);
        }
        add_history(input);
        /* need check value of quotes */
        if (!quotes(input) && set_rl(input, "Quotes not paired", STDERR_FILENO, false))
            continue;
        input = expand(input, envmap, false);
        /* need check value of input */
        tokenizer(input, &chunks);
        /* need check value of chunks */
        syntax = ast_fill(chunks, syntax);
    }
}