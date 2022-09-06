/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:54:59 by ahocine           #+#    #+#             */
/*   Updated: 2022/09/01 19:55:01 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

char	*ft_expender(t_lexer *lexer, char **to_find)
{
	t_env	**env;
	t_env	*tmp;
	char	*res;

	if (!*to_find)
		return (NULL);
	env = ft_get_env();
	tmp = *env;
	if (!lexer)
		return (NULL);
	while (tmp)
	{
		if (!ft_strncmp(*to_find, tmp->str, ft_strlen(tmp->str)))
		{
			res = strdup(tmp->value);
			ft_add_trash((void *)res);
			return (free(*to_find), res);
		}
		tmp = tmp->next;
	}
	return (*to_find);
}
