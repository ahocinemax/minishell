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

static int	ft_parse_flags(char *str, char flag)
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
	if (is_flag && (!str[i] || (str[i] && str[i] != flag)))
		bad_flag = 1;
	i++;
	if (is_flag && str[i] && str[i] != ' ')
		bad_flag = 1;
	return (is_flag && !bad_flag);
}

void	ft_echo(char *var)
{
	int	flag;

	flag = ft_parse_flags(var, 'n');
	if (flag)
			var += 2;
	ft_putstr_fd(var, _STD_OUT);
	if (!flag)
		ft_putchar_fd('\n', _STD_OUT);
}
