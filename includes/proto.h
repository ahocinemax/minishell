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
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define _STD_OUT	1
# define _STD_ERR	2
# define ENV_PATH	""

/////////////////////////////////////////////////////////
//                   PARSEUR - LEXER                   //
/////////////////////////////////////////////////////////

void	ft_parse_args(char *line, t_args *args);
int		ft_check_path(char *path);
t_lexer	*ft_lexer(char *line);
void	ft_parse_cmds(void);

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