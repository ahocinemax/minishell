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
	t_garbage	**next;
	t_garbage	*curr;

	next = ft_get_trash();
	curr = *next;
	while (*next)
	{
		*next = curr->next;
		free(curr->to_free);
		free(curr);
		curr = *next;
	}
	close(0);
	close(1);
	close(2);
	ft_clean_env_list();
}

int	ft_add_trash(void *to_free)
{
	t_garbage	*new_cell;
	t_garbage	**bin;

	bin = ft_get_trash();
	new_cell = (t_garbage *)ft_calloc(sizeof(t_garbage), 1);
	if (!new_cell)
		return (ft_empty_trash(), 0);
	new_cell->to_free = to_free;
	new_cell->next = NULL;
	if (*bin)
		new_cell->next = *bin;
	*bin = new_cell;
	return (1);
}

int	ft_init_trash(void)
{
	t_garbage	**bin;

	bin = ft_get_trash();
	if (!bin)
		return (0);
	*bin = NULL;
	return (1);
}
