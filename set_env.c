# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_env{
	char			*key;
	char			*value;
	struct s_env	*next;

}	t_env;

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_env	*ft_lstnew(void *content, void *key)
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

t_env *ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

char	*ft_strchr(const char *string, int searchedChar)
{
	while (*string)
		if (*string++ == (unsigned char)searchedChar)
			return ((char *)--string);
	if (searchedChar == '\0')
		return ((char *)string);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	if (!*s)
		len = 0;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (len-- != 0 && start < ft_strlen(s))
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}

t_env	*envirement(char *envp[])
{
	t_env	*lst;
	char	*tmp0; // before = key
	char	*tmp1; // after  = value
	int		i;

	i = 0;
	lst = NULL;
	while (envp[i])
	{
		tmp1 = ft_strchr(envp[i], '=') + 1;
		tmp0 = ft_substr(envp[i], 0, tmp1 - envp[i] - 1);
		ft_lstadd_back(&lst, ft_lstnew(tmp1, tmp0));
		i++;
	}
	return(lst);
}

int main(int argc, char const *argv[], char *env[])
{
	t_env *lst = envirement(env);
	while (lst)
	{
		printf("key : %s\n", lst->key);
		printf("value : %s\n", lst->value);
		lst = lst->next;
	}
	return 0;
}

