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
// cp -r ../../includes ../../../0.piscine/|grep \"cat echo\" >> outfile
#include "../../includes/proto.h"

int	g_signal;

static int	ft_check_quote(char *str, char sep)
{
	int	count;
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == sep)
			if (!i || (i && str[i - 1] != '\\'))
				count++;
		i++;
	}
	return (count);
}

void	stop_cmd(int sig)
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
		ft_putstr_fd("Quit (core dumped)\n", _STD_ERR);
		exit (EXIT_FAILURE);
	}
}

static int	check_line(char *str)
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
	if (!(ft_check_quote(str, '\"') % 2) || !(ft_check_quote(str, '\'') % 2))
		return (0);
	return (1);
}

void	ft_free_cmd(t_lexer **command, char *line)
{
	t_lexer	*tmp;

	if (!*command)
		return ;
	while (*command)
	{
		tmp = *command;
		*command = (*command)->next;
		if (tmp->cmd)
			free(tmp->cmd);
		free(tmp);
	}
	if (line)
		free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer	*cmds;
	char	*line;

	if (!ft_init_t_env(envp))
		return (0);
	g_signal = 0;
	cmds = NULL;
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
			free(line);
		else
			ft_parse_cmds(&cmds, line, envp);
	}
	return (0);
}
