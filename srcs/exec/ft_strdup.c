/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 02:35:53 by wmari             #+#    #+#             */
/*   Updated: 2022/09/03 02:36:03 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		len;
	char	*cps;
	char	*save;

	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	save = ptr;
	cps = (char *)s;
	while (len--)
		*ptr++ = *cps++;
	*ptr = '\0';
	return (save);
}
