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

/* <infile cp -r < ../../includes $DISPLAY|grep "cat \"echo\"">>outfile */
char		*ft_heredoc(t_lexer *lexer, char *line);
t_lexer		**ft_split_cmds(t_lexer **lexer);
void		ft_main_parser(char *line);
void    	ft_unlink_heredoc(void);

/*		PARSE_TYPE		*/
void		ft_is_redirect(t_lexer **lexer, char *str, int *index_of_line);
void		ft_is_expend(t_lexer **lexer, char *str, int *index_of_line);
void		ft_is_quote(t_lexer **lexer, char *str, int *index_of_line);
void		ft_is_pipe(t_lexer **lexer, char *s, int *index_of_line);
void		ft_is_str(t_lexer **lexer, char *s, int *index_of_line);
t_lexer		*ft_lexer_type(char *line);

/*		PARSE_CMDS		*/
void		ft_lexer_command(t_lexer *lexer, char *line);
char		*ft_expender(char *env_to_find, int len);
char		*ft_get_path(char *command_to_find);

/*		  UTILS  		*/
void		ft_skip_redir(char *str, int *index);
void		ft_skip_word(char *str, int *index);
int			ft_first_string(t_lexer *lexer);
int			ft_count_pipes(t_lexer *lexer);
int			ft_dont_skip(char c);

/////////////////////////////////////////////////////////
//                     BUILDS - IN                     //
/////////////////////////////////////////////////////////

void		ft_echo(char *var);
void		ft_cd(char *str);
void		ft_unset(char *str);
void		ft_env(char *str);
void		ft_pwd(char *str);
void		ft_export(char *str);

/////////////////////////////////////////////////////////
//                    TOOLS - UTILS                    //
/////////////////////////////////////////////////////////

t_type		ft_find_redir(char *str, int i);
void		ft_skip_redir(char *s, int *i);
/*      trash      */
int			ft_add_trash(void *to_free);
t_garbage	**ft_get_trash(void);
void		ft_empty_trash(void);
int			ft_init_trash(void);
/*       env      */
char		*ft_build_path(t_env *env, char *cmd, int start, int end);
int			ft_init_t_env(char **env);
void		ft_clean_env_list(void);
t_env		**ft_get_env(void);

/////////////////////////////////////////////////////////
//                     EXEC - PART                     //
/////////////////////////////////////////////////////////

char		**get_block_cmd(t_lexer *start, int nb_cmd);
char		**ft_tabstradd(char **old, char *new_str);
char		***create_cmd_blk(t_lexer *start);
int			execute(t_lexer **cmd_block);
int			fork_and_exec(t_lexer *cmd);
int			exec_child(t_lexer *start);
int			builtin_finder(char *name);
int			count_pipe(t_lexer *start);
char		**my_args(t_lexer *start);
void		replug(int stdio_cpy[2]);
int			single_cmd(t_lexer *cmd);
void		replug(int stdio_cpy[2]);
int			single_cmd(t_lexer *cmd);
int			nb_cmd(t_lexer **blck);
char		**get_clean_env(void);
void		free_all(char **tab);

#endif