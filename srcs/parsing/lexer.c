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

static int	isExpension(char c)
{
	return (c == '$');
}

static int	isRedirect(char c)
{
	return (c == '<' || c == '>');
}

t_lexer	*ft_lexer(char *line)
{
	t_lexer	*lex;
	int	i;
	char **split;

	split = ft_split(line, " \"");
	if (!split)
		return (NULL);
	lex = NULL;
	i = 0;
	while (split[i])
	{
		if (split[i][0] && split[i][0] == '-')
			ft_lstadd_back(&lex, ft_lstnew(flag));
		else if (split[i][0] && isRedirect(split[i][0]))
		{
			if (split[i][0] == '<')
			{
				ft_lstlast(lex)->type = infile;
				ft_lstadd_back(&lex, ft_lstnew(redirection));
			}
			else if (split[i][0] == '>')
			{
				ft_lstadd_back(&lex, ft_lstnew(redirection));
				ft_lstadd_back(&lex, ft_lstnew(outfile));
				i++;
			}
		}
		else if (split[i][0] && split[i][0] == '|')
			ft_lstadd_back(&lex, ft_lstnew(pipes));
		else if (split[i][0] && split[i][0] == '$')
			ft_lstadd_back(&lex, ft_lstnew(expender));
		else
			ft_lstadd_back(&lex, ft_lstnew(str));
		free(split[i++]);
	}
	free(split);
	return (lex);
}

int	main(int ac, char **av)
{
	t_lexer	*res;
	if (ac == 2)
	{
		av++;
		res = ft_lexer(*av);
		ft_lstprint(res);
	}
	return (0);
}
