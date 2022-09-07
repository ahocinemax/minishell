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

int	nb_cmd(t_lexer **blck)
{
	int	n;

	n = 0;
	while (blck[n])
		n++;
	return (n);
}

int	piped(t_lexer **cmd_bl)
{
	(void)cmd_bl;
	return (0);
}

int	execute(t_lexer **cmd_block)
{
	int	status;

	status = 0;
	if (cmd_block[0])
	{
		return (single_cmd(cmd_block[0]));
	}
	return (status);
}
		/*if (nb_cmd(cmd_block) > 1)
		{
			printf("ok\n");
			return (piped(cmd_block));
		}
		else */
