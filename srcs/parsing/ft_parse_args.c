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
	while ((*env)->str[start] && (*env)->str[start] != '=')
		start++;
	if ((*env)->str[start] && (*env)->str[start] == '=')
		start++;
	end = start + 1;
	int	i = 0;
	while (fd < 0 && (*env)->str[start] && i < 25)
	{
		while ((*env)->str[end] != ':')
			end++;
		path = malloc(sizeof(char) * (end - start + ft_strlen(cmd) + 2));
		if (!path)
			return (ft_putstr_fd("MALLOC FAILED, NO_PATH\n", _STD_ERR), NULL);
		ft_strlcpy(path, (*env)->str + start, end - start + 1);
		ft_strlcat(path, "/", end - start + 2);
		ft_strlcat(path, cmd, ft_strlen(cmd) + ft_strlen(path) + 1);
		start = end + 1;
		fd = open(path, O_RDONLY);
		if (fd < 0)
			free(path);
		if (end <= start)
			end++;
		i++;
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

int	ft_count_args(t_lexer *lexer)
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

void ft_parse_cmds(t_lexer **lexer, char *line, char **envp)
{
	// t_lexer	*tmp;
	char	**command;
	int		i;
	char	*path_to_cmd;

	*lexer = ft_lexer_type(line);
	// ft_expend(lexer);
	command = ft_lexer_command(lexer, line);
	if (!command)
		return (ft_putstr_fd("MALLOC **CMD FAILED\n", _STD_ERR));
	ft_lstprint(*lexer, TYPE);
	ft_lstprint(*lexer, COMMAND);
	i = -1;
	while (command[++i])
		printf("command[%d] : [%s]\n", i + 1, command[i]);
	(void)path_to_cmd;
	(void)envp;
	ft_free_cmd(cmds, line);
}
