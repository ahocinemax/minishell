/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 12:53:12 by ahocine           #+#    #+#             */
/*   Updated: 2022/09/10 12:53:16 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static char	*ft_find_available_name(void)
{
	char	*res;
	int		fd;
	int		j;

	res = (char *)ft_calloc(sizeof(char), 11);
	if (!res || !ft_add_trash((void *)res))
		return (ft_empty_trash(), NULL);
	ft_strlcat(res, ".heredoc_", 10);
	fd = 0;
	j = 0;
	while (fd != -1 && j < 10)
	{
		if (fd > 0)
			close(fd);
		res[9] = j + '0';
		fd = open(res, O_RDONLY);
		j++;
	}
	return (res);
}

static void	ft_expend_text(char *str, int fd)
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

static void	ft_open_text_area(int fd, bool expend, char *prompt, char *eof)
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
			ft_expend_text(str, fd);
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
	file_name = ft_find_available_name();
	fd = open(file_name, O_CREAT | O_EXCL | O_RDWR, 0644);
	ret = ft_itoa(fd);
	if (!ret || !ft_add_trash((void *)ret))
		return (ft_empty_trash(), NULL);
	if (ft_count_pipes(lexer) > 1)
		prompt = "pipe heredoc> ";
	else
		prompt = "heredoc> ";
	ft_open_text_area(fd, expend, prompt, line);
	return (ret);
}
