/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 00:05:06 by wmari             #+#    #+#             */
/*   Updated: 2022/09/04 05:49:37 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	exec_builtin(t_lexer *cmd)
{
	(void)cmd;
	return (0);
}

void	replug(int fd_cpy[2])
{
	dup2(fd_cpy[0], STDIN_FILENO);
	dup2(fd_cpy[1], STDOUT_FILENO);
}

int	exec_child(t_lexer *start_cmd)
{
	char	**args;
	char	**env;
	int		fd[2];
	t_lexer	*tmp;

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	args = my_args(start_cmd);
	if (!args)
		return (-1);
	env = get_clean_env();
	if (!env)
		return (free_all(args), -1);
	tmp = start_cmd;
	while (tmp && (tmp->type != STRING && tmp->type != CMD))
		tmp = tmp->next;
	if (tmp == NULL)
		return (free_all(args), free_all(env), exit(EXIT_FAILURE), 0);
	execve(tmp->cmd, args, env);
	replug(fd);
	close(fd[0]);
	close(fd[1]);
	return (free_all(args), free_all(env), exit(EXIT_SUCCESS), 0);
}

int	fork_and_exec(t_lexer *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid == -1)
	{
		perror("fork failed");
		return (-1);
	}
	else if (!pid)
		exec_child(cmd);
	else
		wait(&status);
	return (status);
}

int	single_cmd(t_lexer *cmd)
{
	int	fd_cpy[2];
	int	status;

	status = 0;
	if (builtin_finder(cmd->cmd) == -1)
		status = fork_and_exec(cmd);
	else
	{
		fd_cpy[0] = dup(STDIN_FILENO);
		fd_cpy[1] = dup(STDOUT_FILENO);
		status = exec_builtin(cmd);
		replug(fd_cpy);
	}
	return (status);
}
