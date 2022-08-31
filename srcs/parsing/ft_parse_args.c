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

static char *ft_malloc_cmd(t_lexer *lex, char *line)
{
	char *res;
	int len;

	if (lex && lex->next)
		len = lex->next->index - lex->index;
	else
		len = ft_strlen(line + lex->index) + 1;
	if (!len)
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (ft_putstr_fd("MALLOC FAILED, FT_PARSE_ARGS.C", _STD_ERR), NULL);
	res[len] = 0;
	ft_strlcpy(res, line + lex->index, len);
	// printf("%s is in index %d. res is %s\n", lex->type, lex->index, res);
	// printf("%s\n", res);
	return (res);
}

void ft_parse_cmds(t_lexer **lexer, char *line)
{
	t_lexer *tmp;
	char *split;

	// write(1, "ENTER LEXER\n", 11);
	*lexer = ft_lexer(line);
	tmp = *lexer;
	ft_lstprint((t_list *)tmp);
	while (tmp)
	{
		split = ft_malloc_cmd(tmp, line);
		tmp->cmd = split;
		tmp = tmp->next;
	}
	tmp = *lexer;
	while (tmp)
	{
		printf("[%s] ", tmp->cmd);
		if (tmp->next)
			printf("-> ");
		tmp = tmp->next;
	}
}
