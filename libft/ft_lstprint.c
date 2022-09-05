/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:21:21 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/21 21:55:01 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_lexer *lst, int key)
{
	if (!lst)
		ft_putstr_fd("liste vide", _STD_OUT);
	else
	{
		while (lst)
		{
			if (key == COMMAND)
				printf("\e[33m[%s] \e[0m", (char *)lst->cmd);
			else
				printf("\e[31m[%d] \e[0m", lst->type);
			if (lst->next)
				printf("-> ");
			lst = lst->next;
		}
	}
	printf("\n");
}
