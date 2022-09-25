/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:31:35 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/17 18:31:38 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	max(int a, int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

t_lexer	*ft_first_occur_type(t_lexer *lexer, t_type type_to_find)
{
	while (lexer)
	{
		if (lexer->type == type_to_find)
			return (lexer);
		lexer = lexer->next;
	}
	return (NULL);
}

static void	ft_remove_useless_token(t_lexer **start)
{
	t_lexer	*tmp;
	t_lexer	*to_del;

	tmp = *start;
	while (tmp)
	{
		if (tmp->cmd && !*(tmp->cmd))
			tmp->cmd = NULL;
		if (tmp && tmp->next && (tmp->next->type >= REDIRECTION || \
		!tmp->next->cmd))
		{
			to_del = tmp->next;
			tmp->next = to_del->next;
		}
		else if (tmp && (tmp->type >= REDIRECTION || !tmp->cmd) \
		&& tmp == *start)
		{
			*start = tmp->next;
			tmp = *start;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_join_tokens(t_lexer *lexer)
{
	t_lexer	*to_del;
	t_lexer	*tmp;

	if (!lexer)
		return ;
	tmp = lexer;
	while (tmp)
	{
		to_del = tmp->next;
		if (tmp->index && to_del && to_del->index - 1 != ' ')
		{
			tmp->cmd = ft_strjoin(tmp->cmd, to_del->cmd);
			to_del->cmd = NULL;
		}
		tmp = tmp->next;
	}
}

void	ft_main_parser(char *line)
{
	t_lexer	**cmds;
	t_lexer	*lexer;
	int		i;

	i = 0;
	lexer = ft_lexer_type(line);
	if (lexer)
	{
		ft_lexer_command(lexer, line);
		// ft_join_tokens(lexer);
		ft_open_fds(lexer);
		ft_remove_useless_token(&lexer);
		cmds = ft_split_cmds(&lexer);
		if (!cmds)
			return (ft_close_fds());
		while (cmds[i])
		{
			ft_lstprint(cmds[i], TYPE);
			ft_lstprint(cmds[i++], COMMAND);
		}
		ft_execute(cmds);
	}
	ft_close_fds();
	free(cmds);
}
