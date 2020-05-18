/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:42:48 by bcharity          #+#    #+#             */
/*   Updated: 2020/03/28 13:47:02 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define EOC	"\033[0m"
# define RED	"\033[1;31m"
# define YELLOW	"\033[1;33m"
# define WHITE	"\033[1;37m"
# define BLACK	"\033[0;30m"
# define GREEN	"\033[0;32m"
# define BLUE	"\033[0;34m"
# define PURPUL	"\033[0;35m"
# define CYAN	"\033[0;36m"

typedef struct s_list	t_list;

struct			s_list
{
	void		*content;
	size_t		content_size;
	t_list		*next;
};

/*
** vector
*/

typedef struct	s_vector
{
	void		**data;
	int			size;
	int			count;
}				t_vector;

t_vector		*ft_vecnew(void);
int				ft_veccnt(t_vector *v);
void			ft_vecadd(t_vector *v, void *e);
void			ft_vecset(t_vector *v, int index, void *e);
void			*ft_vecget(t_vector *v, int index);
void			*ft_vecgetfirst(t_vector *v);
void			*ft_vecgetlast(t_vector *v);
void			ft_vecdel(t_vector *v, int index);
void			ft_vecfree(t_vector *v);
void			*ft_vecsel(t_vector *vec, size_t off, void *tst, size_t s);

/*
** stack
*/

typedef struct	s_stack
{
	size_t		itop;
	size_t		capacity;
	int			*arr;
}				t_stack;

t_stack			*ft_stack_create(size_t stack_size);
t_stack			*ft_stack_push(t_stack *st, int val);
int				ft_stack_pop(t_stack *src, t_stack *dst, size_t n);
void			ft_stack_swap(t_stack *st);

/*
** gnl
*/

# define MAX_FD 4096
# define BUFF_SIZE 1000

int				get_next_line(const int fd, char **line);
int				to_line(char **line, t_list *node, int ret, int fd);
t_list			*find_fd(t_list **file, int fd);

t_list			*ft_lstnew(void const *content, size_t content_size);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));

void			ft_reverse(int *arr, int dist, size_t size);
void			ft_putnbr_fd(int n, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr(int n);
void			ft_putendl(char const *s);
void			ft_putstr(char const *s);
void			ft_putchar(char c);
char			*ft_itoa(int n);
char			**ft_strsplit(char const *s, char c);
char			*ft_strtrim(char const *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_strequ(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char(*f)(unsigned int, char));
char			*ft_strmap(char const *s, char (*f)(char));
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_strclr(char *s);
void			ft_strdel(char **as);
char			*ft_strnew(size_t size);
void			ft_memdel(void **ap);
void			*ft_memalloc(size_t size);
void			*ft_memset(void *dst, int c, size_t n);
void			ft_bzero(void *dst, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *dst, int c, size_t n);
int				ft_memcmp(const void *mp1, const void *mp2, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *str);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strcat(char *dst, const char *src);
char			*ft_strncat(char *dst, const char *src, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *str, int ch);
char			*ft_strrchr(const char *str, int ch);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack,
				const char *needle, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_freemem(char **split, size_t i);
char			*ft_strreverse(const char *str);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strcopyuntil(char *str, int c);
void			ft_str2del(char ***s);
t_list			*ft_lstcheck_contentsize(t_list **alst, size_t size);
int				ft_lstdel_contentsize(t_list **alst, size_t size);
int				ft_countwords_withnullstr(char const *s, char c);
#endif
