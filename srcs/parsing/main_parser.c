/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:31:35 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/17 18:31:38 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

t_env	*path_env(void)
{
	t_env	**env;
	t_env	*tmp;

	env = ft_get_env();
	if (!*env)
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, "PATH", 5))
			break ;
		tmp = (tmp)->next;
	}
	return (tmp);
}

char	*ft_get_path(char *cmd)
{
	t_env	*env;
	int		fd;
	int		start;
	int		len;
	char	*path;

	env = path_env();
	if (!env)
		return (printf("NO ENV PATH : CANNOT FIND ABSOLUT PATH.\n"), NULL);
	fd = -1;
	start = 0;
	while (fd < 0 && env->value[start])
	{
		len = 1;
		while (env->value[start + len] && env->value[start + len] != ':')
			len++;
		path = ft_build_path(env, cmd, start, len);
		if (!path)
			return (ft_putstr_fd("MALLOC FAILED, NO PATH.\n", _STD_ERR), NULL);
		start += len + 1;
		fd = open(path, O_RDONLY);
	}
	if (fd < 0)
		return (cmd);
	return (close(fd), path);
}

int	ft_cnt_arg(t_lexer *lexer)
{
	int	count;

	count = 0;
	if (!lexer)
		return (0);
	while (lexer && lexer->type != PIPES)
	{
		count++;
		lexer = lexer->next;
	}
	return (count);
}

void	ft_remove_redirection(t_lexer **start)
{
	t_lexer	*tmp;
	t_lexer	*to_del;

	tmp = *start;
	while (tmp)
	{
		if (tmp && tmp->type == REDIRECTION && tmp == *start)
		{
			*start = tmp->next;
			tmp = *start;
		}
		if (tmp && tmp->next && tmp->next->type == REDIRECTION)
		{
			to_del = tmp->next;
			tmp->next = to_del->next;
		}
		tmp = tmp->next;
	}
}

void	ft_main_parser(char *line)
{
	t_lexer	**cmds;
	t_lexer	*lexer;

	lexer = ft_lexer_type(line);
	ft_lstprint(lexer, TYPE);
	ft_lexer_command(lexer, line);
	ft_remove_redirection(&lexer);
	ft_lstprint(lexer, COMMAND);
	cmds = ft_split_cmds(&lexer);
	execute(cmds);
	free(cmds);
}
