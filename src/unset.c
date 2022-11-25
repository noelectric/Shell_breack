/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:01:26 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/21 20:56:43 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_env	*unset(t_env *env, t_env *tmp, t_list *arg)
{
	t_env	*lst;

	while (env)
	{
		if (ft_strcmp(env->key, arg->content))
		{
			lst = ft_lst_new1(env->key, env->value);
			ft_lstadd_back_prime(&tmp, lst);
		}
		env = env->next;
	}
	return (tmp);
}

void	unset_env(t_env **env, t_list *arg)
{
	t_env	*tmp;
	t_env	*env_back;

	tmp = NULL;
	if (ft_strcmp(arg->content, "unset"))
		arg = arg->next->next;
	while (arg && env)
	{
		env_back = (*env);
		if (check(arg) == true)
			return ;
		if (ft_multiple_check((char *)(arg->content)) == 1 \
			&& ft_strcmp(&((char *)arg->content)[0], "_"))
		{
			var.exit_status = 2;
			ft_putendl_fd("invalide inditifier", 2);
		}
		tmp = unset(*env, tmp, arg);
		(*env) = env_back;
		free_env(*env);
		arg = arg->next;
		*env = tmp;
		tmp = NULL;
	}
}

void	free_env(t_env *env)
{
	t_env	*env_back;

	while (env)
	{
		env_back = env;
		free(env->key);
		free(env->value);
		free(env);
		env = env_back->next;
	}
	free(env);
}

bool	check(t_list *arg)
{
	char	*str;

	str = arg->content;
	if (str[0] == '>' || str[0] == '|' || str[0] == '<')
		return (true);
	return (false);
}
