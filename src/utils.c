/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:30:18 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/14 17:51:24 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_list_new1(char *key, char *value)
{
	t_env	*lst;

	lst = (t_env *)malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->key = ft_strdup(key);
	lst->value = ft_strdup(value);
	lst->next = NULL;
	return (lst);
}

void	ft_listadd_back_prime(t_env **lst, t_env *node)
{
	t_env	*head;

	head = *lst;
	if (!head)
	{
		*lst = node;
	}
	else
	{
		while (head->next)
			head = head->next;
		head->next = node;
	}
}