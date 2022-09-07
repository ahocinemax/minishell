/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 00:18:04 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/28 00:18:06 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	ft_is_str(t_lexer **lex, char *s, int *index)
{
	t_lexer	*res;
	t_type	type;

	if (!(*lex) || ft_lstlast(*lex)->type == PIPES || \
	ft_first_string(*lex))
		type = CMD;
	else
		type = STRING;
	res = ft_lstnew(NULL, type, TYPE);
	ft_add_trash((void *)res);
	ft_lstadd_back(lex, res);
	ft_lstlast(*lex)->index = *index;
	(*index)++;
	ft_skip_word(s, index);
}

void	ft_is_pipe(t_lexer **lex, char *s, int *index)
{
	t_lexer	*res;
	int		s_quote;
	int		d_quote;
	int		a;

	s_quote = 0;
	d_quote = 0;
	a = -1;
	while (++a < *index)
	{
		if (s[a] == '\'' && (!a || s[a - 1] == '\\'))
			s_quote++;
		if (s[a] == '\"' && (!a || s[a - 1] == '\\'))
			d_quote++;
	}
	if (d_quote % 2 == 0 && s_quote % 2 == 0)
	{
		res = ft_lstnew(NULL, PIPES, TYPE);
		ft_add_trash((void *)res);
		ft_lstadd_back(lex, res);
		ft_lstlast(*lex)->index = *index;
	}
	(*index)++;
}

void	ft_is_expend(t_lexer **lex, char *s, int *index)
{
	t_lexer	*res;

	if (!s[*index + 1] || (s[*index + 1] && ft_isdigit(s[*index + 1])))
		return ;
	res = ft_lstnew(NULL, EXPENDER, TYPE);
	ft_add_trash((void *)res);
	ft_lstadd_back(lex, res);
	(*index)++;
	ft_lstlast(*lex)->index = *index;
	while (s[*index] && (ft_isalpha(s[*index]) || \
	s[*index] == '_' || ft_isdigit(s[*index])))
		(*index)++;
}

void	ft_is_redirect(t_lexer **lex, char *s, int *i)
{
	t_lexer	*res1;
	t_lexer	*res2;
	t_type	fd_type;

	res1 = ft_lstnew(NULL, REDIRECTION, TYPE);
	ft_add_trash((void *)res1);
	ft_lstadd_back(lex, res1);
	ft_lstlast(*lex)->index = *i;
	fd_type = ft_find_redir(s, *i);
	res2 = ft_lstnew(NULL, fd_type, TYPE);
	ft_add_trash((void *)res2);
	ft_lstadd_back(lex, res2);
	ft_lstlast(*lex)->index = *i;
	ft_skip_redir(s, i);
	ft_lstlast(*lex)->index = *i;
	ft_skip_word(s, i);
}

void	ft_is_quote(t_lexer **lex, char *s, int *i)
{
	char	quote;
	t_lexer	*new;

	new = ft_lstnew(NULL, STRING, TYPE);
	ft_add_trash((void *)new);
	ft_lstadd_back(lex, new);
	new->index = *i;
	quote = s[*i];
	(*i)++;
	while (s + *i && (*(s + *i) != quote || (*(s + *i - 1) == '\\' && \
	*(s + *i) == quote)))
		(*i)++;
	if (s + *i && *(s + *i) == quote)
		(*i)++;
}
