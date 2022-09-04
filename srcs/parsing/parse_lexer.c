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

int	ft_first_string(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		if (tmp->type == CMD)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_is_str(t_lexer **lex, char *s, int *index)
{
	if (!(*lex) || ft_lstlast(*lex)->type == PIPES || \
	ft_first_string(*lex))
		ft_lstadd_back(lex, ft_lstnew(NULL, CMD, TYPE));
	else
		ft_lstadd_back(lex, ft_lstnew(NULL, STRING, TYPE));
	ft_lstlast(*lex)->index = *index;
	(*index)++;
	ft_skip_word(s, index);
}

void	ft_is_pipe(t_lexer **lex, char *s, int *index)
{
	int	s_quote;
	int	d_quote;
	int	a;

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
		ft_lstadd_back(lex, ft_lstnew(NULL, PIPES, TYPE));
		ft_lstlast(*lex)->index = *index;
	}
	(*index)++;
}

void	ft_is_expend(t_lexer **lex, char *s, int *index)
{
	ft_lstadd_back(lex, ft_lstnew(NULL, EXPENDER, TYPE));
	(*index)++;
	ft_lstlast(*lex)->index = *index;
	while (s[*index] >= 'A' && s[*index] <= 'Z')
		(*index)++;
}

void	ft_is_redirect(t_lexer **lex, char *s, int *i)
{
	ft_lstadd_back(lex, ft_lstnew(NULL, REDIRECTION, TYPE));
	ft_lstlast(*lex)->index = *i;
	if (!strncmp(s + *i, "<<", 2))
		ft_lstadd_back(lex, ft_lstnew(NULL, D_INFILE, TYPE));
	else if (!strncmp(s + *i, ">>", 2))
		ft_lstadd_back(lex, ft_lstnew(NULL, D_OUTFILE, TYPE));
	else if (!strncmp(s + *i, "<", 1))
		ft_lstadd_back(lex, ft_lstnew(NULL, INFILE, TYPE));
	else if (!strncmp(s + *i, ">", 1))
		ft_lstadd_back(lex, ft_lstnew(NULL, OUTFILE, TYPE));
	ft_lstlast(*lex)->index = *i;
	(*i)++;
	if (s[*i] && (s[*i] == '>' || s[*i] == '<'))
		(*i)++;
	if (s[*i] && (s[*i] == '>' || s[*i] == '<'))
		ft_putstr_fd("ERROR REDIRECTION SYMBOL\n", _STD_ERR);
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	if (!s[*i] || ft_dont_skip(s[*i]))
		ft_putstr_fd("ERROR REDIRECTION FILE\n", _STD_ERR);
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	ft_lstlast(*lex)->index = *i;
	ft_skip_word(s, i);
}

void	ft_is_quote(t_lexer **lex, char *s, int *i)
{
	char	quote;
	t_lexer	*new;

	new = ft_lstnew(NULL, STRING, TYPE);
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
