/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:31:35 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/17 18:31:38 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

char	*ft_get_path(char **cmd)
{
	t_env	**env;
	t_env	*tmp;
	int		fd;
	int		start;
	int		end;
	char	*path;

	env = ft_get_env();
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, "PATH", 5))
			break ;
		tmp = (tmp)->next;
	}
	if (!(tmp))
		return (printf("NO ENV PATH : CANNOT FIND ABSOLUT PATH.\n"), NULL);
	fd = -1;
	start = 0;
	end = start + 1;
	while (fd < 0 && (tmp)->value[start])
	{
		while (tmp->value[end] != ':')
			end++;
		path = ft_calloc(end - start + ft_strlen(*cmd) + 2, sizeof(char));
		if (!path)
			return (ft_putstr_fd("MALLOC FAILED, NO ABSOLUT PATH\n", _STD_ERR), NULL);
		ft_strlcpy(path, tmp->value + start, end - start + 1);
		ft_strlcat(path, "/", end - start + 2);
		ft_strlcat(path, *cmd, ft_strlen(*cmd) + ft_strlen(path) + 1);
		start = end + 1;
		fd = open(path, O_RDONLY);
		if (fd < 0)
			free(path);
		if (end <= start)
			end++;
	}
	if (fd < 0)
		return (*cmd);
	return (free(*cmd), close(fd), path);
}

char *ft_split_cmd(t_lexer *lex, char *line)
{
	char *res;
	int len;

	if (lex && lex->next)
		len = lex->next->index - lex->index ;
	else
		len = ft_strlen(line + lex->index) + 1;
	res = (char *)ft_calloc(sizeof(char), len + 1);
	if (lex->index && line[lex->index - 1] != ' ')
		len += 1;
	if (!res)
		return (ft_putstr_fd("MALLOC FAILED FT_PARSE_ARGS.C", _STD_ERR), NULL);
	ft_strlcpy(res, line + lex->index, len);
	res[len] = 0;
	char *tmp = res;
	res = ft_strtrim(res, " \t\n\r\v\f");
	free(tmp);
	return (res);
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
			ft_lstdelone(tmp, NULL);
			tmp = *start;
		}
		if (tmp && tmp->next && tmp->next->type == REDIRECTION)
		{
			to_del = tmp->next;
			tmp->next = to_del->next;
			ft_lstdelone(to_del, NULL);
		}
		tmp = tmp->next;
	}
}

void ft_parse_cmds(char *line)
{
	t_lexer **cmds;
	t_lexer	*lexer;

	lexer = ft_lexer_type(line);
	ft_lexer_command(lexer, line);
	ft_remove_redirection(&lexer);
	ft_lstprint(lexer, TYPE);
	ft_lstprint(lexer, COMMAND);
	cmds = ft_split_cmds(&lexer);
	// exec()
	ft_free_cmd(&cmds, line);
}
