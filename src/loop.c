/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:33:53 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/22 00:19:40 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '\"')
			cmd = ft_strchr(cmd + 1, '\"');
		if (cmd == NULL)
			return (0);
		if (*cmd == '\'')
			cmd = ft_strchr(cmd + 1, '\'');
		if (cmd == NULL)
			return (0);
		++cmd;
	}
	return (1);
}

bool	set_rl(char *input, char *output, int fd)
{
	if (input != NULL)
	{
		ft_putstr_fd(input, fd);
		ft_putstr_fd(": ", fd);
	}
	if (input != NULL && output)
	{
		ft_putstr_fd(output, fd);
		ft_putstr_fd("\n", 0);
	}
	return (true);
}

void	ft_control_d(char *input)
{
	if (!input)
	{
		free(input);
		write(1, "exit\n", 5);
		exit(0);
	}
}

char	*read_cmd(t_as **syntax, t_list **chunks)
{
	char	*input;

	*chunks = NULL;
	*syntax = NULL;
	var.id = 0;
	input = readline("SHELL_BREAK > ");
	ft_control_d(input);
	var.usr = ft_strtrim(input, "\t ");
	return (input);
}

void	loop(char *input, t_list *chunks, t_as *syntax, t_env *envmap)
{
	t_fds	fd;

	while (1)
	{
		input = read_cmd(&syntax, &chunks);
		if (!*input && set_rl(NULL, "", 2)
			&& free_loop(input, syntax, &chunks, false))
			continue ;
		add_history(input);
		if (!quotes(input) && set_rl(input, "Quotes error", 2)
			&& free_loop(input, syntax, &chunks, false))
			continue ;
		input = expand(input, envmap, false);
		tokenizer(input, &chunks);
		syntax = ast_fill(chunks, syntax);
		if ((!check_ast(syntax) && set_rl(input, "Syntax error", 2)))
		{
			free_loop(input, syntax, &chunks, true);
			continue ;
		}
		check_cmd(&envmap, chunks, &fd);
		free_loop(input, syntax, &chunks, true);
	}
}
