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

#include "../includes/proto.h"

int	g_signal;

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

static int	ft_check_quote(char *str, char sep)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
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

static int	check_line(char *str)
{
	if (!str)
		return (0);
	return (ft_check_quote(str, '\'') % 2 || ft_check_quote(str, '\"') % 2);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	if (!ft_init_t_env(envp) || !ft_init_trash())
		return (0);
	g_signal = 0;
	signal(SIGINT, stop_cmd);
	signal(SIGQUIT, SIG_IGN);
	if (!argv && !argc)
		return (0);
	while (1)
	{
		line = readline("\e[35mminishell$\e[0m> ");
		add_history(line);
		signal(SIGINT, stop_cmd);
		signal(SIGQUIT, SIG_IGN);
		if (!line || !ft_add_trash((void *)line))
			return (ft_empty_trash(), 1);
		if (check_line(line))
			(ft_putstr_fd("Missing matching quote\n", _STD_ERR));
		else
			ft_main_parser(line);
		stop_cmd(50);
	}
	ft_empty_trash();
	return (0);
}
