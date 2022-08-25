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

static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
			free(split[i++]);
		free(split);
	}
}

static void	is_redirect(t_lexer **lex, char *str, int *i)
{
	if (!strncmp(str, "<<", 2))
	{
		(t_lexer *)ft_lstlast(*lex)->content = double_infile;
		ft_lstadd_back((t_lexer **)lex, (t_lexer *)ft_lstnew(redirection));
		i += 2;
	}
	else if (!strncmp(str, ">>", 2))
	{
		ft_lstadd_back((t_lexer **)lex, (t_lexer *)ft_lstnew(redirection));
		ft_lstadd_back((t_lexer **)lex, (t_lexer *)ft_lstnew(double_outfile));
		i += 2;
	}
	else if (!strncmp(str, '<', 1))
	{
		(t_lexer *)ft_lstlast(*lex)->content = infile;
		ft_lstadd_back((t_lexer **)lex, (t_lexer *)ft_lstnew(redirection));
		i++;
	}
	else if (!strncmp(str, '>', 1))
	{
		ft_lstadd_back((t_lexer **)lex, (t_lexer *)ft_lstnew(redirection));
		ft_lstadd_back((t_lexer **)lex, (t_lexer *)ft_lstnew(outfile));
		i++;
	}
}

t_lexer	*ft_lexer(char *line)
{
	t_lexer	*lex;
	int		i;

	lex = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
			ft_lstadd_back(&lex, ft_lstnew(flag));
		else if ((line[i] == '<' || line[i] == '>'))
			is_redirect(&lex, line + i, &i);
		else if (line[i] == '|')
			ft_lstadd_back(&lex, ft_lstnew(pipes));
		else if (line[i] == '$')
			ft_lstadd_back(&lex, ft_lstnew(expender));
		else if (ft_isspace(line[i]))
			i++;
		else
		{
			ft_lstadd_back(&lex, ft_lstnew(str));
			while (ft_isalpha(line[i]))
				i++;
		}
		i++;
	}
	return (lex);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		av++;
		ft_lstprint(ft_lexer(*av));
	}
	return (0);
}
