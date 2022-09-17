/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 05:38:16 by ahocine           #+#    #+#             */
/*   Updated: 2022/09/04 05:38:19 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

t_env	*ft_find_env(char *env_to_find)
{
	t_env	**env;
	t_env	*tmp;

	env = ft_get_env();
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_name, env_to_find, ft_strlen(tmp->env_name)) \
		&& ft_strlen(env_to_find) == ft_strlen(tmp->env_name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_del_quote(char *str)
{
	char	*res;
	int		i;
	int		c;

	i = 0;
	c = 1;
	res = (char *)ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!res || !ft_add_trash((void *)res))
		return (ft_empty_trash(), NULL);
	while (str[i])
	{
		if ((str[i] != '\'' && str[i] != '\"') || \
		((str[i] == '\'' || str[i] == '\"') && (i && str[i - 1] == '\\')))
			ft_strlcat(res, str + i, c++ + 1);
		i++;
	}
	if (res[ft_strlen(str) - 1] == '\'' || res[ft_strlen(str) - 1] == '\"')
		res[ft_strlen(str) - 1] = 0;
	return (res);
}

int	ft_count_pipes(t_lexer *lexer)
{
	int	count;

	count = 1;
	while (lexer)
	{
		if (lexer->type == PIPES)
			count++;
		lexer = lexer->next;
	}
	return (count);
}

t_lexer	**ft_split_cmds(t_lexer **lexer)
{
	int		nb_pipes;
	int		cmd_id;
	t_lexer	*temp;
	t_lexer	*to_del;
	t_lexer	**cmds;

	cmd_id = 0;
	nb_pipes = ft_count_pipes(*lexer);
	cmds = (t_lexer **)ft_calloc(sizeof(t_lexer *), nb_pipes + 1);
	temp = *lexer;
	while (cmd_id < nb_pipes)
	{
		cmds[cmd_id] = temp;
		while (temp && temp->next && temp->next->type != PIPES)
			temp = temp->next;
		if (temp && temp->next && temp->next->type == PIPES)
		{
			to_del = temp->next;
			temp->next = NULL;
			temp = to_del->next;
		}
		cmd_id++;
	}
	return (cmds);
}
