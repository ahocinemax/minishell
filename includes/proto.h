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

void	ft_parse_cmds(char *line);
void	ft_free_cmd(t_lexer ***command, char *line);
void	ft_remove_redirection(t_lexer **lexer);
t_lexer	**ft_split_cmds(t_lexer **lexer);

/*		PARSE_TYPE		*/
void	ft_is_redirect(t_lexer **lexer, char *str, int *index_of_line);
void	ft_is_expend(t_lexer **lexer, char *str, int *index_of_line);
void	ft_is_quote(t_lexer **lexer, char *str, int *index_of_line);
void	ft_is_pipe(t_lexer **lexer, char *s, int *index_of_line);
void	ft_is_str(t_lexer **lexer, char *s, int *index_of_line);
t_lexer	*ft_lexer_type(char *line);

/*		PARSE_CMDS		*/
char	*ft_expender(t_lexer *lexer, char **env_to_find);
void	ft_lexer_command(t_lexer *lexer, char *line);
char	 *ft_split_cmd(t_lexer *lex, char *line);
char	*ft_get_path(char **command_to_find);
int		ft_check_path(char *path);

/*		  UTILS  		*/
void	ft_skip_word(char *str, int *i);
int		ft_cnt_arg(t_lexer *lexer);
int		ft_count_pipes(t_lexer *lexer);
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
void	ft_clean_env_list(t_env **env);

#endif