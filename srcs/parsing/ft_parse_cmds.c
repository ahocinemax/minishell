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

char	*ft_get_path(char *cmd)
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
		return (printf("ENV PATH IS NULL\n"), NULL);
	fd = -1;
	start = 0;
	end = start + 1;
	while (fd < 0 && (tmp)->value[start])
	{
		while (tmp->value[end] != ':')
			end++;
		path = ft_calloc(end - start + ft_strlen(cmd) + 2, sizeof(char));
		if (!path)
			return (ft_putstr_fd("MALLOC FAILED, NO_PATH\n", _STD_ERR), NULL);
		ft_strlcpy(path, tmp->value + start, end - start + 1);
		ft_strlcat(path, "/", end - start + 2);
		ft_strlcat(path, cmd, ft_strlen(cmd) + ft_strlen(path) + 1);
		start = end + 1;
		fd = open(path, O_RDONLY);
		if (fd < 0)
			free(path);
		if (end <= start)
			end++;
	}
	if (fd < 0)
		return (NULL);
	return (close(fd), path);
}

char *ft_malloc_cmd(t_lexer *lex, char *line)
{
	char *res;
	int len;

	if (lex && lex->next)
		len = lex->next->index - lex->index ;
	else
		len = ft_strlen(line + lex->index) + 1;
	if (len == 1)
		len++;
	res = (char *)ft_calloc(sizeof(char), len + 1);
	if (!res)
		return (ft_putstr_fd("MALLOC FAILED FT_PARSE_ARGS.C", _STD_ERR), NULL);
	ft_strlcpy(res, line + lex->index, len);
	res[len] = 0;
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

static int	ft_not_only_fd_left(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->type != INFILE && lexer->type != OUTFILE && \
		lexer->type != D_INFILE && lexer->type != D_OUTFILE)
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

void	ft_push_fd_back(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp && ft_not_only_fd_left(tmp))
	{
		;
	}
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
		else if (tmp->next && tmp->next->type == REDIRECTION)
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
	// int		id_cmd;
	// char	**split;
	
	// split = ft_split(line, "|");
	cmds = (t_lexer **)ft_calloc(sizeof(t_lexer *), ft_count_pipes(line) + 1);
	cmds[ft_count_pipes(line)] = NULL;
	// id_cmd = -1;
	// while (split[++id_cmd])
	// {
	lexer = ft_lexer_type(line);
	ft_lexer_command(lexer, line);
	// ft_remove_redirection(&lexer);
	ft_lstprint(lexer, TYPE);
	ft_lstprint(lexer, COMMAND);
	// }
}