/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  utils.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 05:04:24 by ahocine           #+#    #+#             */
/*   Updated: 2022/09/07 05:04:26 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	ft_match_quote(char *str, int *i)
{
	char	quote;

	quote = str[(*i)++];
	while ((str[*i] && str[*i] != quote) || \
	(i && str[*i] && str[*i] == quote && str[*i - 1] == '\\'))
		(*i)++;
}

void	ft_skip_word(char *s, int *i)
{
	if (!s)
		return ;
	while (s[*i] && s[*i] != '<' && s[*i] != '>' && s[*i] != '|' && \
		!ft_isspace(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '\"')
			ft_match_quote(s, i);
		(*i)++;
	}
}

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

t_type	ft_find_redir(char *str, int i)
{
	t_type	fd_type;

	fd_type = 0;
	if (!str || !(str + i))
		return (0);
	if (!strncmp(str + i, "<<", 2))
		fd_type = D_INFILE;
	else if (!strncmp(str + i, ">>", 2))
		fd_type = D_OUTFILE;
	else if (!strncmp(str + i, "<", 1))
		fd_type = INFILE;
	else if (!strncmp(str + i, ">", 1))
		fd_type = OUTFILE;
	return (fd_type);
}

void	ft_skip_redir(char *str, int *i)
{
	(*i)++;
	if (str[*i] && (str[*i] == '>' || str[*i] == '<'))
		(*i)++;
	if (str[*i] && (str[*i] == '>' || str[*i] == '<'))
		ft_putstr_fd("ERROR REDIRECTION SYMBOL\n", _STD_ERR);
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}
// if (!str[*i] || (ft_dont_skip(str[*i])))
// 	ft_putstr_fd("ERROR REDIRECTION FILE\n", _STD_ERR);
