/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:21:35 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/18 14:41:38 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	ft_lexer(char *line)
{
	int	nb_flags;
	int	nb_cmds;
	int	nb_args;
	int	i;

	if (!line)
		return ;
	nb_flags = 0;
	nb_args = 0;
	nb_cmds = 0;
	i = 0;
	ft_skip_spaces(line, &i);
	if (line[i] && !ft_isspace(line[i]))
	{
		nb_cmds++;
		while (line[i] && !ft_isspace(line[i]))
			i++;
	}
	ft_skip_spaces(line, &i);
	if (line[i] && line[i] == '-')
	{
		nb_flags++;
		while (line[i] && !ft_isspace(line[i]))
			i++;
	}
	ft_skip_spaces(line, &i);
	while (line[i])
	{
		if (line[i] && !ft_isspace(line[i]))
		{
			nb_args++;
			while (line[i] && !ft_isspace(line[i]))
				i++;
		}
		ft_skip_spaces(line, &i);
	}
	printf("cmds : %d && flags : %d && args : %d\n", nb_cmds, nb_flags, nb_args);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		av++;
		ft_lexer(*av);
	}
	return (0);
}
