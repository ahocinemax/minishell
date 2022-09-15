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

// void	free_file_name(char *file_name)
// {
// 	if (file_name != NULL)
// 	{
// 		unlink(file_name);
// 		free(file_name);
// 	}
// }

int	nb_cmd(t_lexer **block)
{
	int	n;

	n = 0;
	if (!*block)
		return (0);
	while (block[n])
		n++;
	return (n);
}

int	ft_piped(t_lexer **cmd_block)
{
	int		nb_command;
	pid_t	*pid;
	int		i;

	i = 0;
	nb_command = nb_cmd(cmd_block);
	pid = (pid_t *)ft_calloc(sizeof(pid_t), nb_command);
	if (!pid || !ft_add_trash((void *)pid))
		return (ft_empty_trash(), 1);
	while (cmd_block[i])
		ft_single_cmd(cmd_block[i++]);
	return (0);
}

int	ft_execute(t_lexer **cmd_block)
{
	int	status;

	status = 0;
	if (*cmd_block)
	{
		if (nb_cmd(cmd_block) > 1)
			status = ft_piped(cmd_block);
		else
			status = ft_single_cmd(cmd_block[0]);
	}
	return (status);
}
	// free_file_name();
