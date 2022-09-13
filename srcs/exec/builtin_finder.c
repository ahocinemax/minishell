/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 00:06:21 by wmari             #+#    #+#             */
/*   Updated: 2022/09/03 00:06:47 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	builtin_finder(char *name)
{
	static char	*builtin_lookup[7];
	int			i;

	builtin_lookup[0] = "cd";
	builtin_lookup[1] = "pwd";
	builtin_lookup[2] = "exit";
	builtin_lookup[3] = "export";
	builtin_lookup[4] = "env";
	builtin_lookup[5] = "unset";
	builtin_lookup[6] = "echo";
	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(name, builtin_lookup[i], ft_strlen(name)) \
				&& ft_strlen(name) == ft_strlen(builtin_lookup[i]))
			return (i);
		i++;
	}
	return (-1);
}
