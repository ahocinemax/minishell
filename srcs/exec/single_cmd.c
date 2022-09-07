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

int	single_cmd(t_lexer *cmd)
{
	int	stdio_cpy[2];
	int	status;

	status = 0;
	if (builtin_finder(cmd->cmd) == -1)
		status = fork_and_exec(cmd);
	else
	{
		stdio_cpy[0] = dup(STDIN_FILENO);
		stdio_cpy[1] = dup(STDOUT_FILENO);
		status = exec_builtin(cmd);
		replug(stdio_cpy);
	}
	return (status);
}

void	replug(int stdio_cpy[2])
{
	dup2(stdio_cpy[0], STDIN_FILENO);
	dup2(stdio_cpy[1], STDOUT_FILENO);
}

int	fork_and_exec(t_lexer *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (-1);
	}
	if (pid == 0)
		exec_child(cmd);
	else
		wait(&status);
	return (status);
}

int	exec_child(t_lexer *start)
{
	char	**args;
	char	**env;
	int		fd[2];
	t_lexer	*tmp;

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	args = my_args(start);
	if (!args)
		return (-1);
	env = get_clean_env();
	if (!env)
	{
		free_all(args);
		return (-1);
	}
	tmp = start;
	while (tmp && (tmp->type != STRING && tmp->type != CMD))
		tmp = tmp->next;
	if (tmp == NULL)
	{
		free_all(args);
		free_all(env);
		exit(EXIT_FAILURE);
	}
	execve(tmp->cmd, args, env);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	free_all(args);
	free_all(env);
	exit(EXIT_SUCCESS);
}
