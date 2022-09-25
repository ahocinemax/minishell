/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:45:56 by ahocine           #+#    #+#             */
/*   Updated: 2022/09/18 23:46:00 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

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
