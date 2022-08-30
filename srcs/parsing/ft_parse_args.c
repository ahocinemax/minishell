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

static char	*ft_malloc_cmd(t_lexer *lex, char *line)
{
	char	*res;
	int		len;

	if (lex && lex->next)
		len = lex->next->index - lex->index;
	else
		len = ft_strlen(line + lex->index);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (ft_putstr_fd("MALLOC FAILED, FT_PARSE_ARGS.C", _STD_ERR), NULL);
	printf("%d\n", len);
	ft_strlcpy(res, line + lex->index, len);
	return (res);
}

void ft_parse_args(t_cmds **command, char *line)
{
	t_lexer *lex;
	t_lexer *tmp;
	char	*split;

	lex = ft_lexer(line);
	tmp = lex;
	ft_lstprint((t_list *)tmp);
	while (tmp)
	{
		split = ft_malloc_cmd(tmp, line);
		ft_lstadd_back((t_list **)command, ft_lstnew(split));
		printf("[%s]\n", (char *)ft_lstlast((t_list *)(*command))->content);
		tmp = tmp->next;
	}
	ft_lstprint((t_list *)*command);
	free(lex);
	(void)command;
}
