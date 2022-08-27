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

typedef struct s_garbage	t_garbage;
typedef struct s_lexer		t_lexer;
typedef struct s_args		t_args;
typedef struct s_cmds		t_cmds;
typedef struct s_env		t_env;
typedef enum e_type			t_type;

enum e_type
{
	flag,
	str,
	pipes,
	redirection,
	infile,
	double_infile,
	outfile,
	double_outfile,
	expender
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

struct s_garbage
{
	void		*to_free;
	t_garbage	*next;
};

#endif