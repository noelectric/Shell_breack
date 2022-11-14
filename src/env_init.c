#include "../include/minishell.h"


t_env	*ft_lstnew_edit(void *content, void *key)
{
	t_env	*new_element;

	new_element = (t_env *)malloc(sizeof(t_env));
	if (!new_element)
		return (0);
	new_element->value = content;
	new_element->key = key;
	new_element->next = NULL;
	return (new_element);
}


t_env	*envirement(char *envp[])
{
	t_env	*lst;
	char	*tmp0;
	char	*tmp1;
	int		i;

	i = 0;
	lst = NULL;
	while (envp[i])
	{
		tmp1 = ft_strchr(envp[i], '=') + 1;
		tmp0 = ft_substr(envp[i], 0, tmp1 - envp[i] - 1);
		ft_lstadd_back(&lst, ft_lstnew_edit(tmp1, tmp0));
		i++;
	}
	return(lst);
}