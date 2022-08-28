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
	return (c == '<' || c == '>' || c == '|' || c == '$');
}

void	ft_skip_word(char *str, int *i)
{
	while (str[*i] && !ft_dont_skip(str[*i]) && !ft_isspace(str[*i]))
		(*i)++;
}

t_lexer	*ft_lexer(char *s)
{
	t_lexer	*lex;
	int		i;

	lex = NULL;
	i = 0;
	while (s[i])
	{
		if ((s[i] == '<' || s[i] == '>'))
			is_redirect(&lex, s, &i);
		else if (s[i] == '|')
			ft_is_pipe(&lex, &i);
		else if (s[i] == '$')
			ft_is_expend(&lex, s, &i);
		else if ((s[i]) && ft_isspace(s[i]))
			ft_skip_spaces(s, &i);
		else
			ft_is_str(&lex, s, &i);
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
		int i = 0;
		int size = ft_lstsize((t_list *)new);
		while (new)
		{
			switch (new->type)
			{
				case flag:
					printf("FLAG");
					break;
				case str:
					printf("STR");
					break;
				case pipes:
					printf("PIPES");
					break;
				case redirection:
					printf("REDIRECTION");
					break;
				case infile:
					printf("INFILE");
					break;
				case double_infile:
					printf("D_INFILE");
					break;
				case outfile:
					printf("OUTFILE");
					break;
				case double_outfile:
					printf("D_OUTFILE");
					break;
				case expender:
					printf("EXPENDER");
					break;
				default:
					printf("ERR");
			}
			if (i < size - 1)
				printf(" -> ");
			i++;
			tmp = new->next;
			ft_lstdelone((t_list *)new, NULL);
			new = tmp;
		}
		printf("\n");
		free(tmp);
	}
	return (0);
}
