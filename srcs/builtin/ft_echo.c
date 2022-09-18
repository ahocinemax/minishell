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
	while (str[i] && ft_isspace(str[i]) && !is_flag)
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
	int	flg;

	flg = ft_parse_flags(lexer->cmd, 'n');
	if (flg)
			lexer->cmd += 2;
	while (lexer)
	{
		ft_putstr_fd(lexer->cmd, _STD_OUT);
		lexer = lexer->next;
	}
	if (!flg)
		ft_putchar_fd('\n', _STD_OUT);
}
