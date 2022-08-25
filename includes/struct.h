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

typedef struct s_args	t_args;
typedef struct s_cmds	t_cmds;
typedef struct s_env	t_env;
typedef struct s_lexer	t_lexer;
typedef enum   e_type	t_type;

enum e_type
{
	flag,			// 0
	str,			// 1
	pipes,			// 2
	redirection,	// 3
	infile,			// 4
	double_infile,	// 5
	outfile,		// 6
	double_outfile,	// 7
	expender		// 8
};

struct s_args
{
	t_args		*next;
	char		*arg;
};

struct s_cmds
{
	t_cmds		*next;
	char		*cmd;
};

struct s_env
{
	char		*str;
	int			declare;
	t_env		*next;
};

struct s_lexer
{
	t_lexer	*next;
	t_type	type;
};

#endif