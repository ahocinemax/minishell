/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:21:35 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/18 14:41:38 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ft_dont_skip(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '$' || c == '\'' || \
	c == '\"' || c == '\\');
}

void	ft_skip_word(char *s, int *i)
{
	while (s[*i] && !ft_dont_skip(s[*i]) && !ft_isspace(s[*i]))
		(*i)++;
}

void	ft_lexer_command(t_lexer *lex, char *line)
{
	t_lexer	*tmp;
	char	*split;

	if (!lex)
		return ;
	tmp = lex;
	while (tmp)
	{
		split = ft_split_cmd(tmp, line);
		if (tmp->type == EXPENDER)
			tmp->cmd = ft_expender(tmp, &split);
		else if (tmp->type == CMD)
			tmp->cmd = ft_get_path(&split);
		else
			tmp->cmd = split;
		tmp = tmp->next;
	}
}

t_lexer	*ft_lexer_type(char *s)
{
	t_lexer	*lex;
	int		i;

	lex = NULL;
	i = 0;
	if (!s)
		return (NULL);
	while (i < ft_strlen(s))
	{
		if (s[i] == '<' || s[i] == '>')
			ft_is_redirect(&lex, s, &i);
		else if (s[i] == '$')
			ft_is_expend(&lex, s, &i);
		else if ((s[i]) && (ft_isspace(s[i])))
			i++;
		else if ((s[i]) && s[i] == '|')
			ft_is_pipe(&lex, s, &i);
		else if (s[i] == '\'' || s[i] == '\"')
			ft_is_quote(&lex, s, &i);
		else
			ft_is_str(&lex, s, &i);
	}
	return (lex);
}
