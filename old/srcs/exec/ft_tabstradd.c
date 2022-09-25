/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstradd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 02:25:27 by wmari             #+#    #+#             */
/*   Updated: 2022/09/04 00:37:04 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}

static char	**ft_strdupdup(char **tab)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = ft_calloc(i + 2, sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
		{
			free_all(new_tab);
			return (NULL);
		}
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

static char	**ft_create_tab(char *new_str)
{
	char	**tab;

	tab = ft_calloc(3, sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup(new_str);
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

char	*new_line(char *new_str)
{
	char	*temp;
	char	*new_line;

	temp = ft_strdup(new_str);
	if (!temp)
		return (NULL);
	new_line = ft_strtrim(temp, " \t\n\r\v\f");
	free(temp);
	return (new_line);
}

char	**ft_tabstradd(char **old, char *new_str)
{
	int		i;
	char	**new_tab;

	if (!old)
		return (ft_create_tab(new_str));
	else
		new_tab = ft_strdupdup(old);
	if (!new_tab)
		return (NULL);
	i = 0;
	while (new_tab[i])
		i++;
	new_tab[i] = new_line(new_str);
	if (!new_tab[i])
	{
		free_all(new_tab);
		return (NULL);
	}
	new_tab[i + 1] = NULL;
	free_all(old);
	if (old)
		free(old);
	return (new_tab);
}
