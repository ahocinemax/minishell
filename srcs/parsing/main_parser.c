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

void	ft_open_fds(t_lexer *lexer)
{
	t_lexer	*command;
	t_lexer	*tmp;

	command = ft_first_occur_type(lexer, CMD);
	if (!command)
		return ;
	tmp = lexer;
	while (tmp)
	{
		if (tmp->type == INFILE)
			command->fd[0] = open(tmp->cmd, O_RDONLY, 0644);
		else if (tmp->type == OUTFILE)
			command->fd[1] = open(tmp->cmd, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (tmp->type == D_OUTFILE)
			command->fd[1] = open(tmp->cmd, O_RDWR | O_CREAT | O_APPEND, 0644);
		tmp = tmp->next;
	}
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
	if (lexer)
	{
		ft_lexer_command(lexer, line);
		ft_remove_redirection(&lexer);
		ft_open_fds(lexer);
		cmds = ft_split_cmds(&lexer);
		if (!cmds)
			return ;
		while (cmds[i])
		{
			ft_lstprint(cmds[i], TYPE);
			ft_lstprint(cmds[i], COMMAND);
			i++;
		}
		ft_execute(cmds);
	}
	ft_close_fds();
	free(cmds);
}
