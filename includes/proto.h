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

////////////////////////////////////////////////////////
//                   PARSEUR - LEXER                  //
////////////////////////////////////////////////////////

/* <infile cp -r < ../../includes $DISPLAY|grep "cat \"echo\"">>outfile */
char		*ft_heredoc(t_lexer *lexer, char *line);
t_lexer		**ft_split_cmds(t_lexer **lexer);
int			ft_is_strexpend(char *split);
void		ft_main_parser(char *line);
void		ft_unlink_heredoc(void);
void		ft_close_fds(void);

/*		PARSE_TYPE		*/
void		ft_is_redirect(t_lexer **lexer, char *str, int *index_of_line);
void		ft_is_expend(t_lexer **lexer, char *str, int *index_of_line);
void		ft_is_quote(t_lexer **lexer, char *str, int *index_of_line);
void		ft_is_pipe(t_lexer **lexer, char *s, int *index_of_line);
void		ft_is_str(t_lexer **lexer, char *s, int *index_of_line);
t_lexer		*ft_lexer_type(char *line);

/*		PARSE_CMDS		*/
char		*ft_expender(char *env_to_find, int size_elem);
void		ft_lexer_command(t_lexer *lexer, char *line);
char		*ft_get_path(char *command_to_find);

/*		  UTILS  		*/
void		ft_skip_redir(char *str, int *index);
void		ft_skip_word(char *str, int *index);
void		ft_match_quote(char *str, int *i);
int			ft_first_string(t_lexer *lexer);
int			ft_count_pipes(t_lexer *lexer);
char		*ft_del_quote(char *str);
void		signal_cmd_2(int sig);
void		stop_cmd(int signal);

////////////////////////////////////////////////////////
//                     BUILDS - IN                    //
////////////////////////////////////////////////////////

void		ft_export(t_lexer *lexer);
void		ft_unset(t_lexer *lexer);
void		ft_echo(t_lexer *lexer);
void		ft_exit(t_lexer *lexer);
void		ft_env(t_lexer *lexer);
void		ft_pwd(t_lexer *lexer);
void		ft_cd(t_lexer *lexer);

////////////////////////////////////////////////////////
//                    TOOLS - UTILS                   //
////////////////////////////////////////////////////////
/*      redir      */
t_type		ft_find_redir(char *str, int i);
void		ft_skip_redir(char *s, int *i);

/*      trash      */
int			ft_add_trash(void *to_free);
t_garbage	**ft_get_trash(void);
void		ft_empty_trash(void);
int			ft_init_trash(void);

/*       env      */
char		*ft_build_path(t_env *env, char *cmd, int start, int end);
void		ft_add_new_env(char *env_name, char *new_value);
t_env		*ft_find_env(char *env_to_find);
int			ft_init_t_env(char **env);
void		ft_clean_env_list(void);
t_env		**ft_get_env(void);

int			max(int a, int b);

////////////////////////////////////////////////////////
//                     EXEC - PART                    //
////////////////////////////////////////////////////////

int			ft_fork_and_exec_builtin(t_lexer *cmd, int function_index);
char		**get_block_cmd(t_lexer *start, int nb_cmd);
char		**ft_tabstradd(char **old, char *new_str);
char		**ft_args_lst_to_str(t_lexer *start);
char		***create_cmd_blk(t_lexer *start);
int			ft_execute(t_lexer **cmd_block);
void		ft_replug_fd(int stdio_cpy[2]);
int			ft_exec_child(t_lexer *start);
int			ft_builtin_finder(char *name);
int			ft_single_cmd(t_lexer *cmd);
int			fork_and_exec(t_lexer *cmd);
int			count_pipe(t_lexer *start);
int			nb_cmd(t_lexer **blck);
char		**get_clean_env(void);
void		free_all(char **tab);
t_funcptr	*builtin_tab(void);

#endif