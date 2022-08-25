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
	t_lexer	*lexer;
	t_env	**env;
	char	*line;

	env = ft_get_env();
	ft_init_t_env(envp);
	while (1)
	{
		line = readline("minishell$> ");
		add_history(line);
		if (!line)
			return(free(line), 1);
		lexer = ft_lexer(line);
		if (check_line(line))
			return (ERROR);
		else
			ft_exec_cmd(cmd_line, line);
		break ;
	}
	free_all(cmd_line, line);
	return 0;
}
