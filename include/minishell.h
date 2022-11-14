#ifndef MINISHELL_H
#define MINISHELL_H

# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define SIG_INT 2
# define PIPE 0
# define CMD 2
# define RD 1

typedef struct s_lst
{
	void				*content;
	struct s_lst		*next;
}						t_lst;

typedef struct s_env{
	char			*key;
	char			*value;
	struct s_env	*next;

}	t_env;

typedef struct s_as
{
   char         *cmd;
   int		    type;
   struct s_as  *left;
   struct s_as  *right;
}   t_as;

void	ft_free(void **ptr);
bool	ft_isspace(int c);
t_lst	*ft_lstnew(void *content);
t_lst	*ft_lstlast(t_lst *lst);
void	ft_lstdelone(t_lst *lst, void (*del)(void*));
void	ft_lstclear(t_lst **lst, void (*del)(void *));
size_t	ft_strlen(char const *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *string, int searchedChar);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memset(void *s, int c, size_t n);
bool	ft_calloc(void **ptr, size_t cnt, size_t n);
bool	ft_strappend(char **s, char *s2);
char	*expand_last(char *it);
void	expand_space(char *value, t_lst **brace);
char	*expand_brace(t_lst *brace);
char	*expand_middle(char *input, char *it, char *last, t_env *envmap);
char	*expand_internal(char *input, char *it, bool d_quote, t_env *envmap);
char	*expand(char *input, t_env *envmap, bool d_quote);
char	*tokenize_internal(char *input, char *begin, char *end, t_lst **chunks);
void	tokenizer(char *input, t_lst **chunks);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
t_env	*envirement(char *envp[]);
t_env	*ft_lstnew_edit(void *content, void *key);
void	ft_putstr(char *s, int fd);
void	ft_putendl(char *s, int fd);
void	ft_putchar(char c, int fd);
void    loop(char *input, t_lst *chunks, t_as *syntax, t_lst *envmap);
int		ft_strncmp(const char *s1, const char *s2, size_t length);
bool	set_rl(char *input, char *output, int fd, bool nl);
t_as	*ast_fill(t_lst *lst, t_as *syntax);
t_as	*d_add_node(t_as *ast, t_as *node);
t_as	*d_new_node(char *str);
void	free_ast(t_as *ast);

#endif