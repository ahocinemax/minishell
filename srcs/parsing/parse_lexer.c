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
	printf("\e[33mAPPEL DE FT_STR\e[0m\n");
	ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew((void *)str));
	ft_skip_word(s, i);
}

void	ft_is_pipe(t_lexer **lex, char *str, int *i)
{
	printf("\e[34mAPPEL DE FT_PIPE\e[0m\n");
	ft_lstadd_back((t_list **)&lex, ft_lstnew((void *)pipes));
	(void)str;
	(*i)++;
}

void	ft_is_expend(t_lexer **lex, char *str, int *i)
{
	printf("\e[35mAPPEL DE FT_EXP\e[0m\n");
	ft_lstadd_back((t_list **)lex, (t_list *)ft_lstnew((void *)expender));
	(*i)++;
	ft_skip_word(str, i);
}

void	is_redirect(t_lexer **lex, char *str, int *i)
{
	printf("\e[32mAPPEL DE FT_REDIR\e[0m\n");
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
	while (str[*i] && (str[*i] == '>' || str[*i] == '<'))
		(*i)++;
	ft_skip_spaces(str, i);
	ft_skip_word(str, i);
}
