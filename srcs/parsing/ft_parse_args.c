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

static void	ft_trunc_cmd(t_list *command, t_lexer *lexer)
{
	if (lexer->type == string)
		command->content + 1 = 0;
}

void ft_parse_args(t_cmds **command, char *line)
{
	t_lexer *lex;
	t_lexer *tmp;

	lex = ft_lexer(line);
	tmp = lex;
	ft_lstprint((t_list *)lex);
	while (tmp)
	{
		ft_lstadd_back((t_list **)command, ft_lstnew(line + tmp->index));
		if (tmp)
			ft_trunc_cmd(ft_lstlast((t_list *)(*command)), tmp);
		tmp = tmp->next;
		// printf("[%s]\n", (char *)ft_lstlast((t_list *)command)->content);
	}
	// ft_lstprint((t_list *)*command);
	free(lex);
	(void)command;
}
