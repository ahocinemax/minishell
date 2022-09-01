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
		return (0);
	new_env->str = env;
	new_env->declare = declare;
	if (!new_env->str)
		return (0);
	new_env->next = *start;
	*start = new_env;
	return (1);
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

static int	ft_init_env(t_env **env_lst)
{
	char	*str;

	str = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!str)
		return (0);
	if (!ft_add_front("SHLVL=1", env_lst, 1) || !ft_add_front(str, env_lst, 1))
		return (free(str), ft_clean_env_list(env_lst), 0);
	if (!ft_add_front("OLDPWD=", env_lst, 1))
		return (free(str), ft_clean_env_list(env_lst), 0);
	return (free(str), 1);
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
	i = 0;
	while (env[i])
		i++;
	if (!i)
		if (!ft_init_env(env_list))
			return (0);
	i--;
	while (i >= 0)
		if (!ft_add_front(env[i--], env_list, 0))
			return (ft_clean_env_list(env_list), 0);
	return (1);
}
