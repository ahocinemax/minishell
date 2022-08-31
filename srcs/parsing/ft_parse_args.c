/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:31:35 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/17 18:31:38 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ft_count_args(t_lexer *lexer)
{
	int	size;

	size = 0;
	if (!lexer)
		return (0);
	while (lexer && !ft_strncmp(lexer->type, string, 6))
	{
		size++;
		lexer = lexer->next;
	}
	return (size);
}

static char *ft_malloc_cmd(t_lexer *lex, char *line)
{
	char *res;
	int len;

	if (lex && lex->next)
		len = lex->next->index - lex->index;
	else
		len = ft_strlen(line + lex->index) + 1;
	if (len == 1)
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (ft_putstr_fd("MALLOC FAILED FT_PARSE_ARGS.C", _STD_ERR), NULL);
	ft_strlcpy(res, line + lex->index, len);
	return (res);
}

void ft_parse_cmds(t_lexer **lexer, char *line)
{
	t_lexer	*tmp;
	char	*split;
	char	**cmd1;
	int		cmd_size;
	int		i;

	*lexer = ft_lexer(line);
	tmp = *lexer;
	while (tmp)
	{
		split = ft_malloc_cmd(tmp, line);
		tmp->cmd = split;
		tmp = tmp->next;
	}
	cmd_size = ft_count_args(*lexer);
	cmd1 = (char **)malloc(sizeof(char *) * (cmd_size + 1));
	tmp = *lexer;
	i = 0;
	while (i < cmd_size)
	{
		cmd1[i++] = tmp->cmd;
		tmp = tmp->next;
	}
	cmd1[i] = 0;
}
