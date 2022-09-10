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

void	ft_expend_heredoc(char *str, int fd)
{
	char	*expended;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			j = 0;
			while (str[j + i] && (ft_isalpha(str[j + i]) || \
			str[j + i] == '_' || ft_isdigit(str[j + i])))
				j++;
			expended = ft_expender(str + i, j);
			if (expended || ft_strncmp(expended, str, ft_strlen(str)) \
			|| !ft_add_trash((void *)expended))
				write (fd, expended, ft_strlen(expended));
			i += j;
		}
		else
			write(fd, str + i, 1);
		i++;
	}
}

void	ft_open_text_area(int fd, bool expend, char *prompt, char *eof)
{
	char	*str;
	char	*sep;

	sep = ft_strtrim(eof, "\"\'");
	if (!sep || !ft_add_trash((void *)sep))
		return (ft_empty_trash());
	while (1)
	{
		str = readline(prompt);
		if (!str)
			return (free(str));
		if (!ft_strncmp(str, sep, ft_strlen(sep)))
			break ;
		if (*str && expend)
			ft_expend_heredoc(str, fd);
		else if (*str && !expend)
			write(fd, str, ft_strlen(str));
		free(str);
		write(fd, "\n", 1);
	}
	free(str);
}

char	*ft_heredoc(t_lexer *lexer, char *line)
{
	char	*file_name;
	char	*prompt;
	bool	expend;
	char	*ret;
	int		fd;

	if (!line)
		return (NULL);
	expend = false;
	if (*line == '\'')
		expend = true;
	fd = -1;
	while (fd == -1)
	{
		file_name = find_available_name();
		fd = open(file_name, O_CREAT | O_EXCL | O_RDWR, 0644);
	}
	ret = ft_itoa(fd);
	if (!ret || !ft_add_trash((void *)ret))
		return (ft_empty_trash(), NULL);
	if (ft_count_pipes(lexer) > 1)
		prompt = "pipe heredoc> ";
	else
		prompt = "heredoc> ";
	ft_open_text_area(fd, expend, prompt, line);
	close(fd);
	return (ret);
}

static void	ft_remove_redirection(t_lexer **start)
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
	printf("TYPE : ");
	ft_lstprint(lexer, TYPE);
	printf("CMDS : ");
	ft_lstprint(lexer, COMMAND);
	cmds = ft_split_cmds(&lexer);
	free(cmds);
}
	// execute(cmds);
