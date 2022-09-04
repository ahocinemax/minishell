/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 05:38:16 by ahocine           #+#    #+#             */
/*   Updated: 2022/09/04 05:38:19 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ft_count_pipes(t_lexer *lexer)
{
	int	count;

	count = 1;
	while (lexer)
	{
		if (lexer->type == PIPES)
			count++;
		lexer = lexer->next;
	}
	return (count);
}

t_lexer	**ft_split_cmds(t_lexer **lexer)
{
	int		nb_pipes;
	int		cmd_id;
	t_lexer	*temp;
	t_lexer	*to_del;
	t_lexer	**cmds;

	cmd_id = 0;
	nb_pipes = ft_count_pipes(*lexer);
	if (nb_pipes == 1)
		return (cmds = lexer);
	cmds = (t_lexer **)ft_calloc(sizeof(t_lexer *), nb_pipes + 1);
	cmds[cmd_id] = *lexer;
	temp = *lexer;
	while (cmd_id < nb_pipes)
	{
		cmds[cmd_id] = temp;
		while (temp && temp->next && temp->next->type != PIPES)
			temp = temp->next;
		if (temp && temp->next && temp->next->type == PIPES)
		{
			to_del = temp->next;
			temp->next = NULL;
			temp = to_del->next;
			ft_lstdelone(to_del, free);
		}
		printf("tab : %p // cell : %p\n", temp, *lexer);
		cmd_id++;
	}
	cmds[cmd_id] = NULL;
	return (cmds);
}
