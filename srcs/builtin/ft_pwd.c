/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 01:05:51 by ahocine           #+#    #+#             */
/*   Updated: 2022/09/16 01:05:54 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	ft_pwd(t_lexer *lexer)
{
	char	*path;

	if (lexer && lexer->next && lexer->next->type < REDIRECTION)
		return (ft_putstr_fd("pwd: too many arguments\n", _STD_ERR), (void)0);
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}
