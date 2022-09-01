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

void	ft_expender(t_lexer *lexer)
{
	t_env	**env;
	t_lexer	*tmp_lex;

	env = ft_get_env();
	tmp_lex = lexer;
	while (tmp_lex)
	{
		if (!ft_strncmp(tmp_lex->type, EXPENDER, 8))
			break ;
		tmp_lex = tmp_lex->next;
	}
	if (tmp_lex)
	{
		while (*env)
		{
			if (!ft_strncmp(tmp_lex->cmd, (*env)->str, ft_strlen(tmp_lex->cmd)))
			{
				tmp_lex->cmd = (*env)->str;
				break ;
			}
			(*env) = (*env)->next;
		}
	}
}
