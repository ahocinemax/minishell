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

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)), char **envp __attribute__((unused)))
{
	t_lexer	*lexer;
	t_env	**env;
	char	*line;

	env = ft_get_env();
	while (1)
	{
		line = readline("minishell$> ");
		add_history(line);
		if (!line)
			return(free(line));
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
