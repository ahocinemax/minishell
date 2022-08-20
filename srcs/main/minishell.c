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

void	main(int argc, char **argv, char **env)
{
	t_cmds	*cmd_line;
	char	*line;

	(void)argc;
	(void)argv;
	cmd_line = NULL;
	ft_get_env(env);
	while (1)
	{
		// line = readline("minishell$> ");
		// add_history(line);
		// if (!line)
		// 	return(free(line));
		// if (check_line(line))
		// 	return (ERROR);
		// else
		// 	ft_exec_cmd(cmd_line, line);
		break ;
	}
	// free_all(cmd_line, line);
	return ;
}
