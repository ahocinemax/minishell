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

char	*ft_get_path(char **cmd)
{
	t_env	*tmp;
	int		fd;
	int		start;
	int		end;
	char	*path;

	tmp = path_env();
	if (!tmp)
		return (printf("NO ENV PATH : CANNOT FIND ABSOLUT PATH.\n"), NULL);
	fd = -1;
	start = 0;
	end = start + 1;
	while (fd < 0 && tmp->value[start])
	{
		while (tmp->value[end] != ':')
			end++;
		path = ft_calloc(end - start + ft_strlen(*cmd) + 2, sizeof(char));
		if (!path)
			return (ft_putstr_fd("MALLOC FAILED, NO PATH\n", _STD_ERR), NULL);
		ft_add_trash((void *)path);
		ft_strlcpy(path, tmp->value + start, end - start + 1);
		ft_strlcat(path, "/", end - start + 2);
		ft_strlcat(path, *cmd, ft_strlen(*cmd) + ft_strlen(path) + 1);
		start = end + 1;
		fd = open(path, O_RDONLY);
		if (end <= start)
			end++;
	}
	if (fd < 0)
		return (*cmd);
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
	ft_lexer_command(lexer, line);
	ft_remove_redirection(&lexer);
	cmds = ft_split_cmds(&lexer);
	execute(cmds);
}
