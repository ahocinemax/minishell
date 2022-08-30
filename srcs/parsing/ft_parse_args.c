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

void	ft_parse_args(t_cmds **command, char *line)
{
	t_lexer	*lex;
	t_lexer	*tmp;

	lex = ft_lexer(line);
	tmp = lex;
	while (tmp)
	{
		ft_lstadd_back(command);
		tmp = tmp->next;
	}
	ft_lstprint((t_list *)lex);
	free(lex);
	(void)command;
}
