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
	t_env	*tmp;
	t_lexer	*tmp_lex;

	if (!to_find)
		return (NULL);
	env = ft_get_env();
	tmp = *env;
	tmp_lex = *lexer;
	if (tmp_lex)
	{
		while (tmp)
		{
			if (!ft_strncmp(to_find, tmp->str, ft_strlen(tmp->str)))
				return (tmp_lex->cmd = strdup(tmp->value));
			tmp = tmp->next;
		}
	}
	return (NULL);
}
