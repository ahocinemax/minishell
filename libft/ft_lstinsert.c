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

void	ft_lstinsert(t_lexer **start, t_lexer *target, t_lexer *this)
{
	t_lexer	*prev_target;
	int		index_target;
	t_lexer	*prev_this;
	int		index_this;

	if (!start || !target || !this)
		return ;
	index_target = 0;
	prev_target = NULL;
	if (*start != target)
	{
		prev_target = *start;
		while (prev_target && prev_target->next != target)
		{
			index_target++;
			prev_target = prev_target->next;
		}
	}
	index_this = 0;
	prev_this = NULL;
	if (*start != this)
	{
		prev_this = *start;
		while (prev_this && prev_this->next != this)
		{
			index_this++;
			prev_this = prev_this->next;
		}
	}
	if (index_this < index_target)
	{
		if (index_this != 0)
			prev_this->next = this->next;
		else
			*start = this->next;
		prev_target->next = this;
		this->next = target;
	}
	else if (index_target < index_this)
	{
		prev_this->next = this->next;
		if (index_target != 0)
			prev_target->next = this;
		else
			*start = this;
		this->next = target;
	}
}