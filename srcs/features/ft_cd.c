/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:02:24 by ahocine           #+#    #+#             */
/*   Updated: 2022/07/24 16:11:09 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ft_check_path(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	ft_prev_folder(char *path)
{
	int	nb_of_prev;
	int	i;

	if (!path)
		return (0);
	nb_of_prev = 0;
	i = 0;
	while (path[i] == '.')
	{
		if (path[++i] == '.')
		{
			i++;
			if (!path[i] || path[i] == '/')
				nb_of_prev++;
			if (path[i] == '/')
				i++;
		}
	}
	return (nb_of_prev);
}

void	ft_cd(char *str)
{
	char	*path;
	char	*res;
	int		nb_of_prev;
	int		i;

	if (!ft_check_path(str))
	{
		ft_putstr_fd("Can't find directory\n", _STD_ERR);
		return ;
	}
	path = getcwd(NULL, 50);
	nb_of_prev = ft_prev_folder(str);
	while (*str && (*str == '/' || *str == '.'))
		str++;
	if (*(str - 1) == '/')
		str--;
	i = ft_strlen(path) - 1;
	while (nb_of_prev && path[i])
		if (path[i--] == '/')
			nb_of_prev--;
	res = ft_strdup(path);
	res[i + 1] = 0;
	ft_strlcat(res, str, ft_strlen(str));
}

// int	main(int ac, char **av)
// {
// 	if (ac != 2)
// 		return (-1);
// 	av++;
// 	ft_cd(*av);
// 	return (0);
// }
