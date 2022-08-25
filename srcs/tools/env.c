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

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (-1);
	new_env->str = env;
	new_env->declare = declare;
	if (!new_env->str)
		return (-1);
	new_env->next = *start;
	*start = new_env;
	return (0);
}

void	ft_clean_env_list(t_env **env)
{
	t_env	*new;
	t_env	*tmp;

	new = *env;
	tmp = new;
	while (tmp)
	{
		tmp = new;
		new = new->next;
		free(tmp->str);
		free(tmp);
	}
}

static int	ft_init_env(t_env **env_list)
{
	char	*str;

	str = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!str)
		return (-1);
	if (ft_add_front("SHLVL=1", env_list, 1) == -1)
	{
		ft_clean_env_list(env_list);
		return (-1);
	}
	if (ft_add_front(str, env_list, 1) == -1)
	{
		free(str);
		ft_clean_env_list(env_list);
		return (-1);
	}
	free(str);
	if (ft_add_front("OLDPWD=", env_list, 1) == -1)
	{
		ft_clean_env_list(env_list);
		return (-1);
	}
	return (0);
}

t_env	**ft_get_env(void)
{
	static t_env	*new;

	new = NULL;
	return (&new);
}

int	ft_init_t_env(t_env **env)
{
	t_env	**env_list;
	int		i;

	env_list = ft_get_env();
	i = 0;
	while (env[i])
		i++;
	if (!i)
		if (ft_init_env(env[i]) == -1)
			return (-1);
	i--;
	while (i >= 0)
	{
		if (ft_add_front(env[i], env_list, 0) == -1)
		{
			ft_clean_env_list(env_list);
			return (-1);
		}
		i--;
	}
	return (0);
}
