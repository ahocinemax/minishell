/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 04:34:17 by wmari             #+#    #+#             */
/*   Updated: 2022/09/03 04:34:26 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*ptrzero;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ptrzero = (char *)ptr;
	ft_bzero(ptrzero, count * size);
	return (ptr);
}
