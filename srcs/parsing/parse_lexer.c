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

void	ft_skip_word(char *str, int *i);

void	ft_is_str(t_lexer **lex, char *s, int *i)
{
	ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew((void *)str));
	((t_lexer *)ft_lstlast((t_list *)*lex))->index = *i;
	ft_skip_word(s, i);
}

void	ft_is_pipe(t_lexer **lex, char *s, int *i)
{
	int	quote;
	int	a;

	quote = 0;
	a = -1;
	while (++a < *i)
		if (s[a] == '|')
			quote++;
	if (quote % 2 == 0)
		ft_lstadd_back((t_list **)&lex, ft_lstnew((void *)pipes));
	((t_lexer *)ft_lstlast((t_list *)*lex))->index = *i;
	(*i)++;
}

void	ft_is_expend(t_lexer **lex, char *str, int *i)
{
	ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew((void *)expender));
	((t_lexer *)ft_lstlast((t_list *)*lex))->index = *i;
	(*i)++;
	ft_skip_word(str, i);
}

void	is_redirect(t_lexer **lex, char *str, int *i)
{
	ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew((void *)redirection));
	if (!strncmp(str + *i, "<<", 2))
	{
		ft_lstadd_back((t_list **)lex, \
		(t_list *)ft_lstnew((void *)double_infile));
	}
	else if (!strncmp(str + *i, ">>", 2))
	{
		ft_lstadd_back((t_list **)lex, \
		(t_list *)ft_lstnew((void *)double_outfile));
	}
	else if (!strncmp(str + *i, "<", 1))
		ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew((void *)infile));
	else if (!strncmp(str + *i, ">", 1))
		ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew((void *)outfile));
	((t_lexer *)ft_lstlast((t_list *)*lex))->index = *i;
	while (str[*i] && (str[*i] == '>' || str[*i] == '<'))
		(*i)++;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	ft_skip_word(str, i);
}
