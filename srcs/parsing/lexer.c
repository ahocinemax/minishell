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

static int	isRedirect(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&' || c == '$');
}

t_lexer	*ft_lstnew(t_type type)
{
	t_lexer	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->type = type;
	new->next = NULL;
	return (new);
}

static t_lexer	*ft_lstlast(t_lexer *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

static void	ft_lstadd_back(t_lexer **alst, t_lexer *new)
{
	t_lexer	*element;

	if (alst)
	{
		if (*alst)
		{
			element = ft_lstlast(*alst);
			element->next = new;
		}
		else
			*alst = new;
	}
}

static void	ft_lstprint(t_lexer *lst)
{
	if (!lst)
			ft_putstr_fd("liste vide", _STD_OUT);
	else
	{
			while (lst)
			{
					ft_putchar_fd('[', _STD_OUT);
					ft_putnbr_fd(lst->type, _STD_OUT);
					ft_putstr_fd("] ", _STD_OUT);
					lst = lst->next;
			}
	}
	ft_putchar_fd('\n', _STD_OUT);
}


char	**ft_lexer(char *line)
{
	t_lexer	*lex;
	t_lexer	*tmp;
	int	i;
	char **split;

	if (!line)
		return NULL;
	split = ft_split(line, ' ');
	// i = 0;
	// while (split[i])
	// 	printf("{%s}\n", split[i++]);
	lex = NULL;
	i = 0;
	while (split[i])
	{
		if (split[i][0] && split[i][0] == '-')
		{
			ft_lstadd_back(&lex, ft_lstnew(flag));
			i++;
		}
		else if (split[i][0] && isRedirect(split[i][0]))
		{
			ft_lstadd_back(&lex, ft_lstnew(redirection));
			if (split[i][0] == '<')
			{
				tmp = lex;
				while (i--)
					tmp = tmp->next;
				printf("%d\n", tmp->type);
				i = 2;
			}
			i++;
		}
		else
		{
			ft_lstadd_back(&lex, ft_lstnew(str));
			i++;
		}
	}
	ft_lstprint(lex);
	return (split);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		av++;
		ft_lexer(*av);
	}
	return (0);
}
