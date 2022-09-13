/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:37:21 by wmari             #+#    #+#             */
/*   Updated: 2022/09/04 00:01:14 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	free_file_name(char *file_name)
{
	if (file_name != NULL)
	{
		unlink(file_name);
		free(file_name);
	}
}

int	nb_cmd(t_lexer **block)
{
	int	n;

	n = 0;
	while (block[n])
		n++;
	return (n);
}

int	piped(t_lexer **cmd_block)
{
	int		nb_commandd;
	pid_t	*pid;

	nb_commandd = nb_cmd(cmd_block);
	pid = (pid_t *)ft_calloc(sizeof(pid_t), nb_commandd);
	free(pid);
	return (0);
}

int	execute(t_lexer **cmd_block)
{
	int	status;

	status = 0;
	if (*cmd_block)
	{
		if (nb_cmd(cmd_block) > 1)
			status = piped(cmd_block);
		else
			status = single_cmd(cmd_block[0]);
	}
	return (status);
}
// free_file_name();
