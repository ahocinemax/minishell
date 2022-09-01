/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 02:48:46 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/25 02:48:49 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	ft_add_trash(t_garbage **bin, void *to_free)
{
	ft_lstadd_back(bin, ft_lstnew(to_free);)
	(void)to_free;
}
