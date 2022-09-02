/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:21:35 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/18 14:41:38 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ft_dont_skip(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '$' || c == '\'' || \
	c == '\"' || c == '\\');
}

void	ft_skip_word(char *s, int *i)
{
	while (s[*i] && !ft_dont_skip(s[*i]) && !ft_isspace(s[*i]))
		(*i)++;
}

char	**ft_lexer_command(t_lexer **lex, char *line)
{
	t_lexer	*tmp;
	char	**command;
	int		i;
	char	*split;

	command = (char **)malloc(sizeof(char *) * (ft_cnt_arg(*lex) + 1));
	if (!command)
		return (ft_putstr_fd("MALLOC **CMD FAILED\n", _STD_ERR), NULL);
	tmp = *lex;
	i = 0;
	while (tmp)
	{
		split = ft_malloc_cmd(tmp, line);
		// printf("split:%s\n", split);
		if (i < ft_cnt_arg(*lex) && !ft_strncmp(tmp->type, EXPENDER, 8))
			split = ft_expender(&tmp, split);
		if (!split)
			return (ft_putstr_fd("ENV VARIABLE NOT FOUND\n", _STD_ERR), NULL);
		command[i++] = split;
		tmp->cmd = split;
		tmp = tmp->next;
	}
	command[i] = NULL;
	return (command);
}

t_lexer	*ft_lexer_type(char *s)
{
	t_lexer	*lex;
	int		i;

	lex = NULL;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>')
			ft_is_redirect(&lex, s, &i);
		else if (s[i] == '|')
			ft_is_pipe(&lex, s, &i);
		else if (s[i] == '$')
			ft_is_expend(&lex, s, &i);
		else if ((s[i]) && (ft_isspace(s[i])))
			i++;
		else if ((s[i] == '\\' && (s[i + 1] == '\'' || s[i + 1] == '\"')) \
			|| (s[i] == '\'' || s[i] == '\"'))
			ft_is_quote(&lex, s, &i);
		else
			ft_is_str(&lex, s, &i);
	}
	return (lex);
}

// int	main(int ac, char **av)
// {
// 	if (ac == 2)
// 	{
// 		av++;
// 		int len = ft_strlen(*av);
// 		char *arg = (char *)malloc(sizeof(char) * (len + 1));
// 		ft_strlcpy(arg, (const char *)*av, len);
// 		arg[len] = 0;
// 		t_lexer *new = ft_lexer(arg);
// 		t_lexer *tmp = new;
// 		int i = 0;
// 		int size = ft_lstsize((t_list *)new);
// 		ft_lstprint((t_list *)new);
// 		while (i < size)
// 		{
// 			printf("%s\n", arg+tmp->index);
// 			tmp = tmp->next;
// 			i++;
// 		}
// 		free(new);
// 	}
// 	return (0);
// }
