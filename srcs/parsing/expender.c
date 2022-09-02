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

char	*ft_expender(t_lexer **lexer)
{
	t_env	**env;
	t_lexer	*tmp_lex;

	env = ft_get_env();
	tmp_lex = *lexer;
	printf("TO_FIND:%s\n", tmp_lex->cmd);
	if (tmp_lex)
	{
		while (*env)
		{
			printf("ENV:%s\n", (*env)->str);
			if (!ft_strncmp(tmp_lex->cmd, (*env)->str, ft_strlen((*env)->str)))
			{
				tmp_lex->cmd = (*env)->value;
				break ;
			}
			(*env) = (*env)->next;
		}
		return (tmp_lex->cmd);
	}
	return (NULL);
}
