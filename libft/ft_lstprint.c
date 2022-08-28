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

void	ft_lstprint(t_list *lst)
{
	if (!lst)
		ft_putstr_fd("liste vide", _STD_OUT);
	else
	{
		while (lst)
		{

			ft_putchar_fd('[', _STD_OUT);
			printf("%d", *((int *)lst->content));
			// ft_putnbr_fd(*((int *)lst->content), _STD_OUT);
			ft_putstr_fd("] ", _STD_OUT);
			lst = lst->next;
		}
	}
	ft_putchar_fd('\n', _STD_OUT);
}
