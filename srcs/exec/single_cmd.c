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

int	ft_fork_and_exec_builtin(t_lexer *cmd, int function_index)
{
	t_funcptr	*fun_ptr;

	if (!cmd->cmd)
		return (1);
	fun_ptr = builtin_tab();
	if (fun_ptr[function_index])
		fun_ptr[function_index](cmd->next);
	return (0);
}

void	ft_replug_fd(int fd_cpy[2])
{
	dup2(fd_cpy[0], STDIN_FILENO);
	dup2(fd_cpy[1], STDOUT_FILENO);
}

int	ft_exec_child(t_lexer *start_cmd)
{
	char	**args;
	char	**env;
	int		fd[2];
	t_lexer	*tmp;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	args = ft_args_lst_to_str(start_cmd);
	env = get_clean_env();
	if (!args || !env)
		return (free_all(args), free_all(env), -1);
	tmp = start_cmd;
	while (tmp->type > EXPEND_STRING)
		tmp = tmp->next;
	if (tmp == NULL || tmp->cmd == NULL)
		return (free_all(args), free_all(env), exit(EXIT_FAILURE), 0);
	return (execve(tmp->cmd, args, env), ft_replug_fd(fd), close(fd[0]), \
	close(fd[1]), free_all(args), free_all(env), exit(EXIT_SUCCESS), 0);
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
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_exec_child(cmd);
	}
	else
		wait(&status);
	return (status);
}

int	ft_single_cmd(t_lexer *cmd)
{
	int	is_builtin;
	int	fd_cpy[2];
	int	status;

	status = 0;
	is_builtin = ft_builtin_finder(cmd->cmd);
	if (is_builtin == -1)
		status = fork_and_exec(cmd);
	else
	{
		fd_cpy[0] = dup(STDIN_FILENO);
		fd_cpy[1] = dup(STDOUT_FILENO);
		status = ft_fork_and_exec_builtin(cmd, is_builtin);
		ft_replug_fd(fd_cpy);
	}
	signal(SIGINT, stop_cmd);
	signal(SIGQUIT, SIG_IGN);
	return (status);
}
