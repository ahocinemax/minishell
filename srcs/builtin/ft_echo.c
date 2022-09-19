/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:16:40 by ahocine           #+#    #+#             */
/*   Updated: 2022/07/24 14:19:12 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static int	ft_parse_flags(char *str, char flg)
{
	int		bad_flag;
	int		is_flag;
	int		i;

	bad_flag = 0;
	is_flag = 0;
	i = 0;
	while (str[i] && !ft_isspace(str[i]) && !is_flag)
	{
		if (str[i] == '-')
			is_flag = 1;
		i++;
	}
	if (is_flag && (!str[i] || (str[i] && str[i] != flg)))
		bad_flag = 1;
	i++;
	if (is_flag && str[i] && (str[i] != ' ' || str[i] != flg))
		bad_flag = 1;
	return (is_flag && !bad_flag);
}

void	ft_echo(t_lexer *lexer)
{
	t_lexer	*tmp;
	int		flg;

	if (!lexer)
		return ;
	tmp = lexer->next;
	flg = 0;
	if (lexer->fd[0] == 0 && !tmp)
		return (ft_putchar_fd('\n', lexer->fd[1]));
	if (tmp->cmd)
		flg = ft_parse_flags(tmp->cmd, 'n');
	while (tmp && !ft_strncmp(tmp->cmd, "-n", 2))
		tmp = tmp->next;
	while (tmp)
	{
		ft_putstr_fd(tmp->cmd, lexer->fd[1]);
		tmp = tmp->next;
		if (tmp)
			ft_putchar_fd(' ', lexer->fd[1]);
	}
	if (!flg)
		ft_putchar_fd('\n', lexer->fd[1]);
}
