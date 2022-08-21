/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 02:19:40 by ahocine           #+#    #+#             */
/*   Updated: 2022/07/22 02:19:42 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_type
{
	flag,
	str,
	pipes,
	redirection,
	infile,
	outfile
}			t_type;

typedef struct s_args
{
	struct s_args	*next;
	char			*arg;
}				t_args;

typedef struct s_cmds
{
	struct s_cmds	*next;
	char			*cmd;
}				t_cmds;

typedef struct s_lexer
{
	struct s_lexer	*next;
	t_type	type;
}				t_lexer;


typedef struct s_env
{
	char	*str;
	int		declare;
	struct s_env	*next;
}				t_env;

#endif