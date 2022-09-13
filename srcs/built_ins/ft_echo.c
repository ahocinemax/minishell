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
#include <stdio.h>

int	is_expend(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		if (str[i++] == '$')
			return (1);
	return (0);
}

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

void	ft_echo(char *var)
{
	int	flg;

	flg = ft_parse_flags(var, 'n');
	if (flg)
			var += 2;
	if (is_expend(var))
		ft_expend_text(var, _STD_OUT);
	else
		ft_putstr_fd(var, _STD_OUT);
	if (!flg)
		ft_putchar_fd('\n', _STD_OUT);
}
