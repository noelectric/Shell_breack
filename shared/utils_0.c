#include "../include/minishell.h"

void	ft_free(void **ptr)
{
	if (!(ptr && *ptr))
		return ;
	free(*ptr);
	*ptr = NULL;
}

bool	ft_isspace(int c)
{
	return (c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\t');
}
t_lst	*ft_lstnew(void *content)
{
	t_lst	*new_element;

	new_element = (t_lst *)malloc(sizeof(t_lst));
	if (!new_element)
		return (0);
	new_element->content = content;
	new_element->next = NULL;
	return (new_element);
}

t_lst	*ft_lstlast(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}

void	ft_lstdelone(t_lst *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (del)
		del(&(lst->content));
	ft_free((void **)(&lst));
}

void	ft_lstclear(t_lst **lst, void (*del)(void *))
{
	t_lst	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
    
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final;
	size_t	s1_len;
	size_t	s2_len;
	size_t	index;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	final = malloc(s1_len + s2_len + 1);
	if (!final)
		return (NULL);
	index = 0;
	while (s1[index])
	{
		final[index] = s1[index];
		index++;
	}
	index = 0;
	while (s2[index])
	{
		final[s1_len] = s2[index];
		index++;
		s1_len++;
	}
	final[s1_len] = '\0';
	return (final);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (len--)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
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


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	if (dstsize)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	while (src[i])
		++i;
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		((unsigned char *)s)[i] = (unsigned char)c;
	return (s);
}

bool	ft_calloc(void **ptr, size_t cnt, size_t n)
{
	*ptr = (void *)malloc(cnt * n);
	if (!*ptr)
		return (false);
	ft_memset(*ptr, 0, cnt * n);
	return (true);
}



bool	ft_strappend(char **s, char *s2)
{
	char	*s1;

	if (!*s)
	{
		*s = ft_strdup(s2);
		if (!*s)
			return (false);
		return (true);
	}
	s1 = ft_strdup(*s);
	if (!s1)
		return (false);
	ft_free((void **)s);
	if (!ft_calloc((void **)s, ft_strlen(s1) + ft_strlen(s2) + 1, 1))
	{
		ft_free((void **)(&s1));
		return (false);
	}
	ft_strlcpy(*s, s1, ft_strlen(s1) + 1);
	ft_strlcpy(*s + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	ft_free((void **)(&s1));
	return (true);
}

int	ft_strncmp( const char *s1, const char *s2, size_t length )
{
	while ((*s1 || *s2) && length--)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}