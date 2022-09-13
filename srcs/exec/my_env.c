/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 00:54:24 by wmari             #+#    #+#             */
/*   Updated: 2022/09/03 22:40:52 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static char	*create_str_env(t_env *elem)
{
	char	*new;
	char	*news;

	new = ft_strjoin(elem->env_name, "=");
	if (!new)
		return (NULL);
	news = ft_strjoin(new, elem->value);
	free(new);
	return (news);
}

char	**get_clean_env(void)
{
	t_env	**lst_env;
	t_env	*cpy;
	char	**new_env;
	char	*str;

	lst_env = ft_get_env();
	new_env = NULL;
	cpy = *lst_env;
	while (cpy)
	{
		str = create_str_env(cpy);
		if (!str)
			free_all(new_env);
		new_env = ft_tabstradd(new_env, str);
		free(str);
		if (!new_env)
			return (NULL);
		cpy = cpy->next;
	}
	return (new_env);
}
