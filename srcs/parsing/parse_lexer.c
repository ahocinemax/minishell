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
	// write(1, "ENTER IsSTR\n", 11);
	ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew(string));
	(*i)++;
	((t_lexer *)ft_lstlast((t_list *)*lex))->index = *i;
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
	if (d_quote % 2 == 0 && s_quote % 2 == 	0)
	{
		ft_lstadd_back((t_list **)&lex, (t_list *)ft_lstnew(pipes));
		((t_lexer *)ft_lstlast((t_list *)*lex))->index = *i;
	}
	(*i)++;
}

void	ft_is_expend(t_lexer **lex, char *s, int *i)
{
	ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew(expender));
	((t_lexer *)ft_lstlast((t_list *)*lex))->index = *i;
	(*i)++;
	ft_skip_word(s, i);
}

void	ft_is_redirect(t_lexer **lex, char *s, int *i)
{
	ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew(redirection));
	((t_lexer *)ft_lstlast((t_list *)*lex))->index = *i;
	if (!strncmp(s + *i, "<<", 2))
		ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew(d_infile));
	else if (!strncmp(s + *i, ">>", 2))
		ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew(d_outfile));
	else if (!strncmp(s + *i, "<", 1))
		ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew(infile));
	else if (!strncmp(s + *i, ">", 1))
		ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew(outfile));
	((t_lexer *)ft_lstlast((t_list *)*lex))->index = *i;
	(*i)++;
	if (s[*i] && (s[*i] == '>' || s[*i] == '<'))
		(*i)++;
	if (s[*i] && (s[*i] == '>' || s[*i] == '<'))
		printf("ERROR REDIRECTION SYMBOL\n");
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	if (!s[*i] || ft_dont_skip(s[*i]))
		printf("ERROR REDIRECTION FILE\n");
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	((t_lexer *)ft_lstlast((t_list *)*lex))->index = *i;
	ft_skip_word(s, i);
}

void	ft_is_quote(t_lexer **lex, char *s, int *i)
{
	char	quote;
	t_lexer	*new;

	new = (t_lexer *)ft_lstnew(string);
	ft_lstadd_back((t_list **)lex, (t_list *)new);
	new->index = *i;
	quote = s[*i];
	(*i)++;
	while (s + *i && *(s + *i) != quote)
		(*i)++;
	if (s + *i && *(s + *i) == quote)
		(*i)++;
}
