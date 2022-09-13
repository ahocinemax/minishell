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

void	ft_close_fds(t_lexer **cmds)
{
	t_lexer	*tmp;
	int		fd;
	int		i;

	i = 0;
	while (cmds[i])
	{
		tmp = cmds[i];
		while (tmp)
		{
			if (tmp->type > 4)
			{
				fd = ft_atoi(tmp->cmd);
				if (fd > 0)
					close(fd);
			}
			tmp = tmp->next;
		}
		i++;
	}
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

	lexer = ft_lexer_type(line);
	ft_lexer_command(lexer, line);
	ft_remove_redirection(&lexer);
	cmds = ft_split_cmds(&lexer);
	execute(cmds);
	ft_close_fds(cmds);
	free(cmds);
}
// while (cmds[i])
// int	i = 0;
// {
// 	ft_lstprint(cmds[i], TYPE);
// 	ft_lstprint(cmds[i], COMMAND);
// 	i++;
// }
