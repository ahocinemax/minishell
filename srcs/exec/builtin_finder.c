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

int	ft_builtin_finder(char *name)
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

t_funcptr	*builtin_tab(void)
{
	static t_funcptr	builtin_pointer[7];

	builtin_pointer[0] = ft_cd;
	builtin_pointer[1] = ft_pwd;
	builtin_pointer[2] = ft_exit;
	builtin_pointer[3] = ft_export;
	builtin_pointer[4] = ft_env;
	builtin_pointer[5] = ft_unset;
	builtin_pointer[6] = ft_echo;
	return (builtin_pointer);
}
