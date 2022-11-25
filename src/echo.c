/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:02 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/22 00:25:51 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	depannage(char *tmp, t_list *tmp1)
{
	while (tmp1)
	{
		if (tmp1->flag == 1)
		{
			printf("%s", tmp);
			return ;
		}
		tmp1 = tmp1->next;
	}
	printf("%s\n", tmp);
	return ;
}

void	echo(t_list *arg)
{
	char	*tmp;
	t_list	*tmp1;
	int		i;

	i = 0;
	arg->flag = 0;
	tmp1 = arg;
	if (arg && (!arg->next || !ft_strcmp(arg->next->content, "\0")))
		return (printf("\n"), (void)arg);
	if (ft_strcmp(arg->content, "echo"))
		arg = arg->next->next;
	arg = arg->next;
	i = check_newline(arg) + 1;
	while (--i != 0)
	{
		arg->flag = 1;
		arg = arg->next;
	}
	tmp = join_echo(arg);
	depannage(tmp, tmp1);
	free(tmp);
}

char	*join_echo(t_list *arg)
{
	char	*output;
	char	*tmp;

	output = ft_strdup("");
	while (arg)
	{
		tmp = removechar(arg->content);
		if ((!ft_strcmp(tmp, ">")) || (!ft_strcmp(tmp, ">>")))
		{
			arg = arg->next->next;
			free(tmp);
			if (arg == NULL)
				break ;
			else
				tmp = removechar(arg->content);
		}
		if (!ft_strcmp(tmp, "|"))
			return (free(tmp), output);
		output = ft_strjoin_custom(output, tmp);
		free(tmp);
		if (arg->next)
			output = ft_strjoin_custom(output, " ");
		arg = arg->next;
	}
	return (output);
}

int	check_newline(t_list *arg)
{
	char	**tmp;
	t_list	*tmp1;
	int		i;
	int		j;
	int		k;

	k = 0;
	tmp1 = arg;
	while (tmp1)
	{
		tmp = ft_split(tmp1->content, '-');
		i = 0;
		while (tmp[i])
		{
			j = 0;
			while (tmp[i][j++] == 'n')
				if (!tmp[i][j])
					k++;
			i++;
		}
		ft_free_2d(tmp);
		tmp1 = tmp1->next;
	}
	return (k);
}
