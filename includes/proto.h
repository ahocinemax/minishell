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
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

extern int	g_signal;

/////////////////////////////////////////////////////////
//                   PARSEUR - LEXER                   //
/////////////////////////////////////////////////////////

void	ft_parse_cmds(t_lexer **commands, char *line, char **envp);
int		ft_check_path(char *path);
t_lexer	*ft_lexer(char *line);

void	ft_is_redirect(t_lexer **lex, char *str, int *i);
void	ft_is_expend(t_lexer **lex, char *str, int *i);
void	ft_is_pipe(t_lexer **lex, char *s, int *i);
void	ft_is_str(t_lexer **lex, char *s, int *i);
void	ft_is_quote(t_lexer **lex, char *str, int *i);

void	ft_skip_word(char *str, int *i);
int		ft_dont_skip(char c);

/////////////////////////////////////////////////////////
//                     BUILDS - IN                     //
/////////////////////////////////////////////////////////

void	ft_echo(char *var);
void	ft_cd(char *str);

/////////////////////////////////////////////////////////
//                    TOOLS - UTILS                    //
/////////////////////////////////////////////////////////

void	ft_add_trash(void *to_free);
int		ft_init_t_env(char **env);
t_env	**ft_get_env(void);

#endif