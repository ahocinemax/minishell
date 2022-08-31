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

void	ft_is_str(t_lexer **lex, char *s, int *i)
{
	ft_lstadd_back(lex, ft_lstnew(string, TYPE));
	ft_lstlast(*lex)->index = *i;
	(*i)++;
	ft_skip_word(s, i);
}

void	ft_is_pipe(t_lexer **lex, char *s, int *i)
{
	int	s_quote;
	int	d_quote;
	int	a;

	s_quote = 0;
	d_quote = 0;
	a = -1;
	while (++a < *i)
	{
		if (s[a] == '\'')
			s_quote++;
		if (s[a] == '\"')
			d_quote++;
	}
	if (d_quote % 2 == 0 && s_quote % 2 == 0)
	{
		ft_lstadd_back(lex, ft_lstnew(pipes, TYPE));
		ft_lstlast(*lex)->index = *i;
	}
	(*i)++;
}

void	ft_is_expend(t_lexer **lex, char *s, int *i)
{
	ft_lstadd_back(lex, ft_lstnew(expender, TYPE));
	ft_lstlast(*lex)->index = *i;
	(*i)++;
	ft_skip_word(s, i);
}

void	ft_is_redirect(t_lexer **lex, char *s, int *i)
{
	ft_lstadd_back(lex, ft_lstnew(redirection, TYPE));
	ft_lstlast(*lex)->index = *i;
	if (!strncmp(s + *i, "<<", 2))
		ft_lstadd_back(lex, ft_lstnew(d_infile, TYPE));
	else if (!strncmp(s + *i, ">>", 2))
		ft_lstadd_back(lex, ft_lstnew(d_outfile, TYPE));
	else if (!strncmp(s + *i, "<", 1))
		ft_lstadd_back(lex, ft_lstnew(infile, TYPE));
	else if (!strncmp(s + *i, ">", 1))
		ft_lstadd_back(lex, ft_lstnew(outfile, TYPE));
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

	new = ft_lstnew(string, TYPE);
	ft_lstadd_back(lex, new);
	new->index = *i;
	if (s[*i] == '\\')
		(*i)++;
	quote = s[*i];
	(*i)++;
	while (s + *i && *(s + *i) != quote)
		(*i)++;
	if (s + *i && *(s + *i) == quote)
		(*i)++;
}
