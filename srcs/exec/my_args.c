/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 06:05:35 by wmari             #+#    #+#             */
/*   Updated: 2022/09/04 05:02:01 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

char	**my_args(t_lexer *start)
{
	t_lexer	*tmp;
	char	**my_arg;
	int		fd;

	tmp = start;
	my_arg = NULL;
	while (tmp)
	{
		if (tmp->type == INFILE)
		{
			fd = open(ft_strtrim(tmp->cmd, " \t\n\r\v\f"), O_RDONLY);
			if (fd == -1)
			{
				free_all(my_arg);
				return (NULL);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			tmp = tmp->next;
			continue ;
		}
		else if (tmp->type == OUTFILE)
		{
			fd = open(ft_strtrim(tmp->cmd, " \t\n\r\v\f"), O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (fd == -1)
			{
				free_all(my_arg);
				return (NULL);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			tmp = tmp->next;
			continue ;
		}
		else if (tmp->type != STRING && tmp->type != CMD)
		{
			tmp = tmp->next;
			continue ;
		}
		my_arg = ft_tabstradd(my_arg, tmp->cmd);
		if (!my_arg)
			return (NULL);
		tmp = tmp->next;
	}
	return (my_arg);
}
