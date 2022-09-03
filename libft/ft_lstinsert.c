/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 01:51:46 by ahocine           #+#    #+#             */
/*   Updated: 2022/09/03 01:51:49 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstinsert(t_lexer **start, t_lexer *insert_here, t_lexer *this)
{
	t_lexer	*tmp;

	if (!start || !insert_here || !this)
		return ;
	tmp = *start;
	while (tmp && tmp->next != insert_here)
		tmp = tmp->next;
	if (tmp && tmp->next == insert_here)
	{
		tmp->next = this;
		this->next = insert_here;
	}
}