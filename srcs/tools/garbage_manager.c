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
		printf("removing \e[30m[%p] \e[0mfrom trash\n", curr->to_free);
		free(curr->to_free);
		free(curr);
		curr = *next;
	}
	ft_clean_env_list();
}

void	ft_add_trash(void *to_free)
{
	t_garbage	*new_cell;
	t_garbage	**bin;
	t_garbage	*tmp;

	bin = ft_get_trash();
	new_cell = ft_calloc(sizeof(t_garbage), 1);
	if (!new_cell)
		ft_empty_trash();
	new_cell->to_free = to_free;
	new_cell->next = NULL;
	printf("adding \e[33m[%p] \e[0mto trash\n", new_cell->to_free);
	tmp = *bin;
	while (tmp)
	{
		tmp = tmp->next;
	}
	
}
