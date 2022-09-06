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

t_garbage	**ft_get_trash(void)
{
	static t_garbage	*bin;

	return (&bin);
}

void	ft_empty_trash(void)
{
	t_garbage	**bin;
	t_garbage	*tmp;

	bin = ft_get_trash();
	tmp = *bin;
	while (*bin)
	{
		*bin = tmp->next;
		free(tmp);
		tmp = *bin;
	}
	ft_clean_env_list();
}

void	ft_add_trash(void *to_free)
{
	t_garbage	**bin;
	t_lexer		*new_cell;

	bin = ft_get_trash();
	new_cell = ft_lstnew(to_free, 0, COMMAND);
	if (!new_cell)
		ft_empty_trash();
	ft_lstadd_back((t_lexer **)bin, new_cell);
}
