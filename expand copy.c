#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*expand(char *input, bool d_quote);

typedef struct s_lst
{
	void				*content;
	struct s_lst		*next;
}						t_lst;

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
		if (*string++ == (unsigned castreeshar)searchedChar)
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

static inline char	*expand_last(char *it)
{
	if (*it && ft_strchr("$?", *it))
		++it;
	else
		while (*it && !ft_strchr(" ><\'\"|?$", *it))
			++it;
	return (it);
}

void	expand_space(char *value, t_lst **brace)
{
	t_lst	*append;
	char	*search;

	*brace = NULL;
	search = value;
    append = NULL;
	while (true)
	{
		search = ft_strchr(value, ' ');
		if (search == NULL)
			break ;
		*search++ = '\0';
		append = ft_lstnew(ft_strdup(value));
        if (append != NULL && append->content != NULL)
            exit (0); 
		value = search;
		ft_lstadd_back(brace, append);
	}
	if (!*value)
		return ;
	append = ft_lstnew(ft_strdup(value));
    if (append == NULL && append->content == NULL)
        return ;
	ft_lstadd_back(brace, append);
}

char	*expand_brace(t_lst *brace)
{
	bool	ret;
	char	*middle;
	t_lst	*origin;

	middle = NULL;
	origin = brace;
	ret = ft_strappend(&middle, (char *)(brace->content));
    if (ret == false)
        exit (0);
	while (brace->next != NULL)
	{
		brace = brace->next;
		ret = ft_strappend(&middle, " ");
		if (ret == false)
            exit (0); 
		ret = ft_strappend(&middle, (char *)(brace->content));
		if (ret == false)
            exit (0); 
	}
	// ft_lstclear(&origin, (void **)ft_free);
	return (middle);
}

char	*expand_middle(char *input, char *it, char *last)
{
	char	*key;
	char	*value;
	t_lst	*brace;

	if (last - it == 1)
		return (ft_strdup("$"));
	key = ft_substr(input, it - input + 1, last - it - 1);
	value = "xterm-256color";
	if (value == NULL)
		value = "";
	ft_free((void **)(&key));
	value = ft_strdup(value);
	if (value == NULL || !*value)
		return (value);
	expand_space(value, &brace);
    if (brace == NULL)
        return 0;
	ft_free((void **)(&value));
	return (expand_brace(brace));
}

char *removeChar(char *str)
{
    int		i;
	int		j;
    int		len;
    char	*tmp;

	len = strlen(str);
    tmp = ft_strdup(str);
	i = 0;
    while (i < len)
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			j = i;
			while (j < len)
				tmp[j++] = tmp[j+1];
			len--;
			i--;
		}
		i++;
	}
    return(tmp);
}

char	*expand_internal(char *input, char *it, bool d_quote)
{
	char	*first;
	char	*last;
	char	*middle;
	char	*former;
	char	*latter;

	first = ft_substr(input, 0, it - input);
	last = expand_last(it + 1);
	middle = expand_middle(input, it, last);
	last = ft_strdup(last);
	former = ft_strjoin(first, middle);
	latter = expand(last, d_quote);
	ft_free((void **)(&middle));
	ft_free((void **)(&first));
	input = ft_strjoin(former, latter);
	ft_free((void **)(&latter));
	ft_free((void **)(&former));
	input = removeChar(input);
	return (input);
}
char	*expand(char *input, bool d_quote)
{
	char	*iter;    

	if (input == NULL)
		return (NULL);
	iter = input;
	while (*iter)
	{
		if (*iter == '\"')
			d_quote = !d_quote;
		else if (*iter == '\'' && !d_quote)
			iter = ft_strchr(iter + 1, '\'');
		else if (*iter == '<' && *(iter + 1) == '<' && !d_quote)
		{
			iter += 2;
			while (*iter && ft_isspace(*iter))
				++iter;
			while (*iter && !ft_isspace(*iter))
				++iter;
		}
		if (*iter == '$')
			return (expand_internal(input, iter, d_quote));
		if (*iter)
			++iter;
	}
	return (input);
}

char	*tokenize_internal(char *input, char *begin, char *end, t_lst **chunks)
{
	char	*token;
	t_lst	*temp;

	token = ft_substr(input, begin - input, end - begin + 1);
	temp = ft_lstnew(token);
	ft_lstadd_back(chunks, temp);
	return (end + 1);
}

void	tokenizer(char *input, t_lst **chunks)
{
	char	*begin;
	char	*end;

	begin = input;
	while (*begin)
	{
		while (!ft_isspace)
			++begin;
		end = begin;
		while (*end && !ft_strchr(" ><|", *begin))
		{
			if (ft_strchr("\'\"", *end))
				end = ft_strchr(end + 1, *end);
			if (ft_strchr("><|", *(end + 1)))
				break ;
			++end;
		}
		if (!*end)
			--end;
		if (*begin && *begin == *(begin + 1) && ft_strchr("><", *begin))
			++end;
		if (*begin)
			begin = tokenize_internal(input, begin, end, chunks);
	}
}


int main(int ac, char *av[], char *envp[])
{
    char *input = "echo \"$\"\"T\"\"E\"\"R\"\"M\" $TERM$TERM$TERM$TERM$TERM$TERM";
    t_lst	*chunks = NULL;
	input = expand(input, false);

	printf("%s\n", input);
	while(1);
    return 0;
}