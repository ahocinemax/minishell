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

static int	ft_handle_fd(t_lexer *tmp)
{
	int	fd;

	if (tmp->type == INFILE || tmp->type == D_INFILE)
	{
		fd = open(tmp->cmd, O_RDONLY);
		if (fd == -1)
			return (0);
		dup2(fd, STDIN_FILENO);
	}
	else if (tmp->type == OUTFILE || tmp->type == D_OUTFILE)
	{
		fd = open(tmp->cmd, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			return (0);
		dup2(fd, STDOUT_FILENO);
	}
	return (close(fd), 1);	
}

char	**my_args(t_lexer *start)
{
	t_lexer	*tmp;
	char	**my_arg;

	tmp = start;
	my_arg = NULL;
	while (tmp)
	{
		if (tmp->type == INFILE || tmp->type == D_INFILE || \
		tmp->type == OUTFILE || tmp->type == D_OUTFILE)
		{
			if (!ft_handle_fd(tmp))
				return (free_all(my_arg), NULL);
		}
		else if (tmp->type != STRING && tmp->type != CMD)
			continue ;
		my_arg = ft_tabstradd(my_arg, tmp->cmd);
		if (!my_arg)
			return (NULL);
		tmp = tmp->next;
	}
	return (my_arg);
}
