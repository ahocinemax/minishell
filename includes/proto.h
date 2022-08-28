/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 02:19:40 by ahocine           #+#    #+#             */
/*   Updated: 2022/07/22 02:19:42 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "struct.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ENV_PATH	""

extern	int	g_signal;

/////////////////////////////////////////////////////////
//                   PARSEUR - LEXER                   //
/////////////////////////////////////////////////////////

void	ft_parse_args(char *line, t_cmds **commands);
int		ft_check_path(char *path);
t_lexer	*ft_lexer(char *line);
void	ft_parse_cmds(t_cmds **commands, char *line);

void	ft_is_expend(t_lexer **lex, char *str, int *i);
void	is_redirect(t_lexer **lex, char *str, int *i);
void	ft_is_str(t_lexer **lex, char *s, int *i);
void	ft_is_pipe(t_lexer **lex, char *s, int *i);

/////////////////////////////////////////////////////////
//                     BUILDS - IN                     //
/////////////////////////////////////////////////////////

void	ft_echo(char *var);
void	ft_cd(char *str);

/////////////////////////////////////////////////////////
//                    TOOLS - UTILS                    //
/////////////////////////////////////////////////////////

t_env	**ft_get_env(void);
void	ft_add_trash(void *to_free);

#endif