/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:12:07 by ahocine           #+#    #+#             */
/*   Updated: 2022/07/27 16:17:29 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ft_add_front(char *env, t_env **start, int declare)
{
	t_env	*new_env;
	int		i;

	i = 0;
	new_env = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new_env)
		return (0);
	new_env->env_name = env;
	while (env[i])
	{
		if (env[i++] == '=')
		{
			env[i - 1] = '\0';
			new_env->value = env + i;
		}
	}
	new_env->declare = declare;
	if (!new_env->value)
		return (0);
	new_env->next = *start;
	*start = new_env;
	return (1);
}

void	ft_clean_env_list(void)
{
	t_env	**get_env;
	t_env	*next;
	t_env	*curr;

	get_env = ft_get_env();
	next = *get_env;
	while (next)
	{
		curr = next;
		next = curr->next;
		free(curr);
	}
}

static int	ft_init_env(t_env **env_lst)
{
	char	*path;
	char	*str;

	path = getcwd(NULL, 0);
	if (!path)
		return (ft_clean_env_list(), 0);
	if (!ft_add_trash((void *)path))
		return (ft_empty_trash(), 0);
	str = ft_strjoin("PWD=", path);
	if (!str)
		return (0);
	if (!ft_add_trash((void *)str))
		return (ft_empty_trash(), 0);
	if (!ft_add_front("SHLVL=1", env_lst, 1) || !ft_add_front(str, env_lst, 1))
		return (ft_clean_env_list(), 0);
	if (!ft_add_front("OLDPWD=", env_lst, 1))
		return (ft_clean_env_list(), 0);
	return (1);
}

t_env	**ft_get_env(void)
{
	static t_env	*new;

	return (&new);
}

int	ft_init_t_env(char **env)
{
	t_env	**env_list;
	int		i;

	env_list = ft_get_env();
	if (!env_list)
		return (0);
	*env_list = NULL;
	i = 0;
	while (env[i])
		i++;
	if (!i)
		if (!ft_init_env(env_list))
			return (0);
	i--;
	while (i >= 0)
		if (!ft_add_front(env[i--], env_list, 0))
			return (ft_clean_env_list(), 0);
	return (1);
}
