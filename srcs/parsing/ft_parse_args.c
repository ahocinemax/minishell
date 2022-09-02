/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
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
	int		fd;
	int		start;
	int		end;
	char	*path;

	env = ft_get_env();
	while (*env)
	{
		if (ft_strnstr((*env)->str, "PATH=", 5))
			break ;
		*env = (*env)->next;
	}
	if (!(*env))
		return (NULL);
	fd = -1;
	start = 0;
	end = start + 1;
	while (fd < 0 && (*env)->value[start])
	{
		while ((*env)->value[end] != ':')
			end++;
		path = malloc(sizeof(char) * (end - start + ft_strlen(cmd) + 2));
		if (!path)
			return (ft_putstr_fd("MALLOC FAILED, NO_PATH\n", _STD_ERR), NULL);
		ft_strlcpy(path, (*env)->value + start, end - start + 1);
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
	res = (char *)malloc(sizeof(char) * (len + 1));
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
	while (lexer && ft_strncmp(lexer->type, PIPES, 5))
	{
		count++;
		lexer = lexer->next;
	}
	return (count);
}

void ft_parse_cmds(t_lexer **lexer, char *line)
{
	char	**command;

	*lexer = ft_lexer_type(line);
	command = ft_lexer_command(lexer, line);
	ft_lstprint(*lexer, TYPE);
	ft_lstprint(*lexer, COMMAND);
	if (!command || !*lexer)
		return (ft_putstr_fd("PARSING FAILED. ABORT\n", _STD_ERR));
	ft_free_cmd(lexer, line);
}
