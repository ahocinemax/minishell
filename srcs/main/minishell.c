/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 02:16:40 by ahocine           #+#    #+#             */
/*   Updated: 2022/07/22 02:16:42 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"
#include "../../includes/struct.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmds;

	ft_init_t_env(envp);
	signal(SIGINT, stop_cmd);
	signal(SIGQUIT, SIG_IGN);
	if (!av && !ac)
		return (0);
	while (1)
	{
		line = readline("minishell$> ");
		add_history(line);
		signal(SIGINT, stop_cmd);
		signal(SIGQUIT, SIG_IGN);
		if (!line)
			return(free(line), 1);
		if (check_line(line))
			return (ERROR);
		else
			ft_exec_cmd(cmd_line, line);
		free_cmd();
	}
	return 0;
}
