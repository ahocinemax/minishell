/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 22:12:09 by ahocine           #+#    #+#             */
/*   Updated: 2021/06/28 22:12:22 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lexer	*ft_lstnew(char *content, int val, int key)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	if (key == COMMAND)
		new->cmd = content;
	else
		new->type = val;
	new->next = NULL;
	new->index = 0;
	return (new);
}
