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

static int	ft_dont_skip(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '$');
}

static void	is_redirect(t_lexer **lex, char *str, int *i)
{
	if (!strncmp(str, "<<", 2))
	{
		ft_lstlast((t_list *)*lex)->content = (void *)double_infile;
		ft_lstadd_back((t_list **)lex, \
		(t_list *)ft_lstnew((void *)redirection));
		i += 2;
	}
	else if (!strncmp(str, ">>", 2))
	{
		ft_lstadd_back((t_list **)lex, \
		(t_list *)ft_lstnew((void *)redirection));
		ft_lstadd_back((t_list **)lex, \
		(t_list *)ft_lstnew((void *)double_outfile));
		i += 2;
	}
	else if (!strncmp(str, "<", 1))
	{
		ft_lstlast((t_list *)*lex)->content = (void *)infile;
		ft_lstadd_back((t_list **)lex, \
		(t_list *)ft_lstnew((void *)redirection));
		i++;
	}
	else if (!strncmp(str, ">", 1))
	{
		ft_lstadd_back((t_list **)lex, \
		(t_list *)ft_lstnew((void *)redirection));
		ft_lstadd_back((t_list **)lex, \
		(t_list *)ft_lstnew((void *)outfile));
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
		{
			if (line[i + 1] && ft_isalnum(line[i + 1]))
			{
				ft_lstadd_back((t_list **)&lex, ft_lstnew((void *)flag));
				while (line[i] && (!ft_isspace(line[i]) && !ft_dont_skip(line[i])))
					i++;
			}
			else
				i++;
		}
		else if ((line[i] == '<' || line[i] == '>'))
		{
			is_redirect(&lex, line + i, &i);
			printf("%c\n", line[i]);
			i++;
		}
		else if (line[i] == '|')
		{
			ft_lstadd_back((t_list **)&lex, ft_lstnew((void *)pipes));
			i++;
		}
		else if (line[i] == '$')
		{
			ft_lstadd_back((t_list **)&lex, ft_lstnew((void *)expender));
			i++;
		}
		else if ((line[i]) && ft_isspace(line[i]))
			i++;
		else
		{
			ft_lstadd_back((t_list **)&lex, ft_lstnew((void *)str));
			while (line[i] && !ft_isspace(line[i]) && !ft_dont_skip(line[i]))
				i++;
		}
	}
	ft_lstlast((t_list *)lex)->next = NULL;
	return (lex);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		av++;
		int len = ft_strlen(*av);
		char *arg = (char *)malloc(sizeof(char) * (len + 1));
		ft_strlcpy(arg, (const char *)*av, len);
		arg[len] = 0;
		t_lexer *new = ft_lexer(arg);
		t_lexer *tmp;
		while (new)
		{
			printf("[%d] ", new->type);
			tmp = new->next;
			ft_lstdelone((t_list *)new, NULL);
			new = tmp;
		}
		printf("\n");
		free(tmp);
	}
	return (0);
}
