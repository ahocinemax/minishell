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

void	ft_add_new_env(char *new_name, char *new_value)
{
	t_env	**env;
	t_env	*tmp;

	env = ft_get_env();
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_name, new_name, ft_strlen(tmp->env_name)))
			return (tmp->value = new_value, (void)1);
		tmp = tmp->next;
	}
}

void	ft_cd(t_lexer *lex)
{
	char	*path;
	t_env	*home;

	if (!lex || lex->cmd[0] == '~')
	{
		home = ft_find_env("HOME");
		if (home)
			path = home->value;
		else
			return (ft_putstr_fd("$HOME is not set.\n", _STD_ERR), (void)0);
	}
	else
	{
		path = (char *)getcwd(NULL, 1000);
		if (!path || !ft_add_trash((void *)path))
			return (ft_empty_trash());
		ft_strlcat(path, "/", ft_strlen(path) + 2);
		ft_strlcat(path, lex->cmd, ft_strlen(path) + ft_strlen(lex->cmd) + 1);
	}
	ft_add_new_env("OLDPWD", path);
	if (chdir(path) == -1)
		return (ft_putstr_fd("Folder does not exist.\n", _STD_ERR), (void)0);
	path = getcwd(NULL, 0);
	if (!path || !ft_add_trash((void *)path))
		return (ft_empty_trash());
	ft_add_new_env("PWD", path);
}
