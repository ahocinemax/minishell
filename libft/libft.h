/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:08:08 by ahocine           #+#    #+#             */
/*   Updated: 2021/06/24 19:00:36 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# ifndef _STD_OUT
#  define _STD_OUT	1
# endif
# ifndef _STD_ERR
#  define _STD_ERR	2
# endif
# define COMMAND	0
# define TYPE		1

typedef struct s_list	t_list;
typedef struct s_lexer	t_lexer;
typedef enum e_type		t_type;

enum	e_type
{
	STRING,
	CMD,
	PIPES,
	EXPENDER,
	EXPEND_STRING,
	REDIRECTION,
	INFILE,
	D_INFILE,
	OUTFILE,
	D_OUTFILE
};

struct s_list
{
	t_list	*next;
	void	*content;
};

struct s_lexer
{
	int		index;
	t_type	type;
	char	*cmd;
	t_lexer	*next;
};

/*	Linked lists	*/
t_lexer	*ft_lstnew(char *content, int val, int key);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_lexer *lst);
t_lexer	*ft_lstlast(t_lexer *lst);
void	ft_lstadd_back(t_lexer **alst, t_lexer *new);
void	ft_lstdelone(t_lexer *lst, void (*del)(void *));
void	ft_lstclear(t_lexer **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstprint(t_lexer *lst, int key);
void	ft_free_arr(void **array);
void	ft_lstpush_back(t_lexer **start, t_lexer *this);

/*	Mandatory		*/
void	*ft_memset(void *dest, int c, size_t len);
void	ft_bzero(void *b, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memccpy(void *dest, const void *src, int c, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memchr(const void *b, int c, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t len);
void	ft_skip_spaces(char *line, int *i);
int		ft_strlen(const char *str);
int		ft_issep(char c, char *sep);
int		ft_isspace(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_arrsize(char **array);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *big, const char	*little, size_t len);
int		ft_atoi(const char *nb);
void	*ft_calloc(size_t number, size_t len);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(const char *str, char *charset);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif
