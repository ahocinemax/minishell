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

void	ft_skip_expend(char *str, int *i)
{
	*i = 0;
	while (str[*i] && (ft_isalpha(str[*i]) || \
	str[*i] == '_' || ft_isdigit(str[*i])))
		(*i)++;
}

static char	*ft_expend_text2(char *str)
{
	char	*exp;
	char	*res;
	int		i;
	int		j;

	i = -1;
	res = (char *)ft_calloc(sizeof(char), 10000);
	if (!ft_add_trash((void *)res))
		return (ft_empty_trash(), NULL);
	while (++i < ft_strlen(str))
	{
		if (str[i] == '$')
		{
			i++;
			ft_skip_expend(str + i, &j);
			exp = ft_expender(str + i, j);
			if (exp && ft_strncmp(exp, str, i - j))
				ft_strlcat(res, exp, ft_strlen(exp) + 2);
			i += j;
		}
		else
			ft_strlcat(res, str + i, i + 2);
	}
	return (res);
}

static char	*ft_split_cmd(t_lexer *lex, char *line)
{
	char	*res;
	int		len;

	if (lex && lex->next)
		len = lex->next->index - lex->index ;
	else
		len = ft_strlen(line + lex->index) + 1;
	res = (char *)ft_calloc(sizeof(char), len + 1);
	if (!res)
		return (ft_putstr_fd("MALLOC FAILED FT_SPLIT_ARGS.C", _STD_ERR), NULL);
	if (!ft_add_trash((void *)res))
		return (NULL);
	if (line[lex->index] != ' ')
		len++;
	ft_strlcpy(res, line + lex->index, len);
	res = ft_strtrim(res, " \t\n\r\v\f");
	res = ft_del_quote(res);
	if (!res)
		return (NULL);
	if (!ft_add_trash((void *)res))
		return (NULL);
	return (res);
}

void	ft_lexer_command(t_lexer *lexer, char *line)
{
	t_lexer	*tmp;
	char	*split;

	if (!lexer)
		return ;
	tmp = lexer;
	while (tmp)
	{
		split = ft_split_cmd(tmp, line);
		if (tmp->type == EXPENDER)
			tmp->cmd = ft_expender(split, ft_strlen(split));
		else if (tmp->type == CMD)
			tmp->cmd = ft_get_path(split);
		else if (tmp->type == D_INFILE)
			tmp->cmd = ft_heredoc(tmp, split);
		else if (tmp->type == EXPEND_STRING)
			tmp->cmd = ft_expend_text2(split);
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
		else if (s[i] && ft_isspace(s[i]))
			i++;
		else if (s[i] && s[i] == '|')
			ft_is_pipe(&lex, s, &i);
		// else if (s[i] == '\'' || s[i] == '\"')
		// 	ft_is_quote(&lex, s, &i);
		else
			ft_is_str(&lex, s, &i);
	}
	return (lex);
}
