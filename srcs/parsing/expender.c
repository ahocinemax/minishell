/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:54:59 by ahocine           #+#    #+#             */
/*   Updated: 2022/09/01 19:55:01 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

char	*ft_expend_string(char *split)
{
	char	*res;
	int		i;

	if (!split)
		return (NULL);
	res = NULL;
	i = 0;
	while(split[i])
	{
		if (i == '$')
		{
			;
		}
		else
		
	}
	return (res);

}

t_env	*path_env(void)
{
	t_env	**env;
	t_env	*tmp;

	env = ft_get_env();
	if (!*env)
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_name, "PATH", 5))
			break ;
		tmp = (tmp)->next;
	}
	return (tmp);
}

char	*ft_get_path(char *cmd)
{
	t_env	*env;
	int		fd;
	int		start;
	int		len;
	char	*path;

	env = path_env();
	if (!env)
		return (printf("NO ENV PATH : CANNOT FIND ABSOLUT PATH.\n"), NULL);
	fd = -1;
	start = 0;
	while (fd < 0 && env->value[start])
	{
		len = 1;
		while (env->value[start + len] && env->value[start + len] != ':')
			len++;
		path = ft_build_path(env, cmd, start, len);
		if (!path)
			return (ft_putstr_fd("MALLOC FAILED, NO PATH.\n", _STD_ERR), NULL);
		start += len + 1;
		fd = open(path, O_RDONLY);
	}
	if (fd < 0)
		return (cmd);
	return (close(fd), path);
}

char	*ft_expender(char *to_find, int len)
{
	t_env	**env;
	t_env	*tmp;
	char	*res;

	if (!to_find)
		return (NULL);
	res = "\0";
	env = ft_get_env();
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(to_find, tmp->env_name, len))
		{
			res = strdup(tmp->value);
			if (!ft_add_trash((void *)res))
				return (ft_empty_trash(), NULL);
			return (res);
		}
		tmp = tmp->next;
	}
	return (res);
}

char	*ft_build_path(t_env *path, char *cmd, int start, int len)
{
	char	*res;

	res = ft_calloc(len + ft_strlen(cmd) + 2, sizeof(char));
	if (!res)
		return (NULL);
	if (!ft_add_trash((void *)res))
		return (ft_empty_trash(), NULL);
	ft_strlcpy(res, path->value + start, len + 1);
	ft_strlcat(res, "/", len + 2);
	ft_strlcat(res, cmd, ft_strlen(cmd) + ft_strlen(res) + 1);
	return (res);
}
