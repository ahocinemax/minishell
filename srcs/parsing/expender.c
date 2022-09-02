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

char	*ft_expender(t_lexer **lexer, char *to_find)
{
	t_env	**env;
	t_lexer	*tmp_lex;

	if (!to_find)
		return (NULL);
	env = ft_get_env();
	tmp_lex = *lexer;
	if (tmp_lex)
	{
		while (*env)
		{
			if (!ft_strncmp(to_find, (*env)->str, ft_strlen((*env)->str)))
				return (tmp_lex->cmd = strdup((*env)->value));
			(*env) = (*env)->next;
		}
	}
	return (NULL);
}
