/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:37:21 by wmari             #+#    #+#             */
/*   Updated: 2022/09/04 00:01:14 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	nb_cmd(t_lexer **block)
{
	int	n;

	n = 0;
	if (!*block)
		return (0);
	while (block[n])
		n++;
	return (n);
}

int	ft_no_fork_needed(t_lexer *cmd_line)
{
	int	builtin_index;
	int	fd_cpy[2];
	int status;

	builtin_index = ft_builtin_finder(cmd_line->cmd);
	fd_cpy[0] = dup(STDIN_FILENO);
	fd_cpy[1] = dup(STDOUT_FILENO);
	status = ft_exec_builtin(cmd_line, builtin_index, 1);
	ft_replug_fd(fd_cpy);
	signal(SIGINT, stop_cmd);
	signal(SIGQUIT, SIG_IGN); 
	return (status);
}

int	ft_piped(t_lexer **cmd_block)
{
	int		status;
	pid_t	*pid;
	int		i;

	i = 0;
	status = 0;
	pid = (pid_t *)ft_calloc(sizeof(pid_t), nb_cmd(cmd_block));
	if (!pid || !ft_add_trash((void *)pid))
		return (ft_empty_trash(), 1);
	while (cmd_block[i])
		status = ft_single_cmd(cmd_block[i++], (*pid)++);
	return (status);
}

int	ft_execute(t_lexer **cmd_block)
{
	int	status;

	status = 0;
	if (*cmd_block)
	{
		if (nb_cmd(cmd_block) > 1 || (cmd_block[0]->fd[0] != 0 || \
		cmd_block[0]->fd[1] != 1) || ft_builtin_finder((*cmd_block)->cmd))
			status = ft_piped(cmd_block);
		else
			status = ft_no_fork_needed(cmd_block[0]);
	}
	return (status);
}
