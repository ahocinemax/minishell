/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:31:35 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/17 18:31:38 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	ft_parse_args(char *line, t_args **stack)
{
	char	**split;
	int		len;
	size_t	i;
	t_args	*args;
	t_args	*new;

	if (!line)
		return ;
	i = 0;
	split = ft_split(line, 32);
	len = ft_arrsize(split);
	args = ft_lstnew(NULL);
	while (split[i])
	{
		ft_lstnew(split[i++]);
		ft_lstadd_back(&args, new);
		args = args->next;
	}
	return ;
}
