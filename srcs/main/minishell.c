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

int	ft_quote(char *str, char sep)
{
	int	count;
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == sep)
			c++;
		i++;
	}
	return (c);
}

void	signal_cmd(int sig)
{
	g_signal += sig;
	if (sig == 2)
	{
		g_signal = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		ft_putchar_fd("Quit (core dumped)\n", _STD_ERR);
		exit (1);
	}
}

int	check_str(char *str)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '|')
			dif = 1;
		if (str[i] == '|')
		{
			if (dif == 0)
				return (0);
			dif = 0;
		}
		i++;
	}
	if (!(ft_quote(str, '\"') % 2) || !(ft_quote(str, '\'') % 2))
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmds	*cmds;
	char	*line;
	t_lexer	*lex;

	ft_init_t_env(envp);
	signal(SIGINT, stop_cmd);
	signal(SIGQUIT, SIG_IGN);
	if (!argv && !argc)
		return (0);
	while (1)
	{
		line = readline("minishell$> ");
		add_history(line);
		signal(SIGINT, stop_cmd);
		signal(SIGQUIT, SIG_IGN);
		if (!line)
			return (free(line), 1);
		if (check_line(line))
			return (free(line), 0);
		// else
		// 	ft_exec_cmd(cmd_line, line);
		// free_cmd();
		free(line);
	}
	return (0);
}
