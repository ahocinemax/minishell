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

void	ft_close_fds(void)
{
	int		fd;

	fd = 2;
	while (fd < 10)
		close(fd++);
	ft_unlink_heredoc();
}

static void	ft_remove_redirection(t_lexer **start)
{
	t_lexer	*tmp;
	t_lexer	*to_del;

	tmp = *start;
	while (tmp)
	{
		if (tmp && tmp->type == REDIRECTION && tmp == *start)
		{
			*start = tmp->next;
			tmp = *start;
		}
		if (tmp && tmp->next && tmp->next->type == REDIRECTION)
		{
			to_del = tmp->next;
			tmp->next = to_del->next;
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
	ft_lexer_command(lexer, line);
	ft_remove_redirection(&lexer);
	cmds = ft_split_cmds(&lexer);
	while (cmds[i])
	{
		ft_lstprint(cmds[i], TYPE);
		ft_lstprint(cmds[i], COMMAND);
		i++;
	}
	ft_execute(cmds);
	ft_close_fds();
	free(cmds);
}
