/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  utils.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 05:04:24 by ahocine           #+#    #+#             */
/*   Updated: 2022/09/07 05:04:26 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

char	*ft_build_path(t_lexer *lexer)
{
	char	*path;

	path = ft_calloc(end - start + ft_strlen(*cmd) + 2, sizeof(char));
	if (!path)
		return (NULL);
	ft_add_trash((void *)path);
	ft_strlcpy(path, lexer->value + start, end - start + 1);
	ft_strlcat(path, "/", end - start + 2);
	ft_strlcat(path, cmd, ft_strlen(cmd) + ft_strlen(path) + 1);
	return (path);
}

int	ft_first_string(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		if (tmp->type == CMD)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_type	ft_find_redir(char *str, int i)
{
	t_type	fd_type;

	fd_type = 0;
	if (!strncmp(str + i, "<<", 2))
		fd_type = D_INFILE;
	else if (!strncmp(str + i, ">>", 2))
		fd_type = D_OUTFILE;
	else if (!strncmp(str + i, "<", 1))
		fd_type = INFILE;
	else if (!strncmp(str + i, ">", 1))
		fd_type = OUTFILE;
	return (fd_type);
}

void	ft_skip_redir(char *str, int *i)
{
	(*i)++;
	if (str[*i] && (str[*i] == '>' || str[*i] == '<'))
		(*i)++;
	if (str[*i] && (str[*i] == '>' || str[*i] == '<'))
		ft_putstr_fd("ERROR REDIRECTION SYMBOL\n", _STD_ERR);
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	if (!str[*i] || ft_dont_skip(str[*i]))
		ft_putstr_fd("ERROR REDIRECTION FILE\n", _STD_ERR);
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}
