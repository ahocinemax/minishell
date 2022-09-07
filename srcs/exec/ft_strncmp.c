/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:16:47 by wmari             #+#    #+#             */
/*   Updated: 2022/09/02 21:41:27 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	n = n - 1;
	while ((*ptrs1 == *ptrs2) && (n-- > 0) && *ptrs1 && *ptrs2)
	{
		ptrs1++;
		ptrs2++;
	}
	return (*ptrs1 - *ptrs2);
}
