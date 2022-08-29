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

# define flag 				"flag"
# define string				"string"
# define pipes				"pipes"
# define redirection		"redirection"
# define infile				"infile"
# define d_infile			"double_infile"
# define outfile			"outfile"
# define d_outfile			"double_outfile"
# define expender			"expender"

typedef struct s_garbage	t_garbage;
typedef struct s_lexer		t_lexer;
typedef struct s_cmds		t_cmds;
typedef struct s_env		t_env;
// typedef enum e_type			t_type;
// enum e_type
// {
// 	flag,
// 	str,
// 	pipes,
// 	redirection,
// 	infile,
// 	d_infile,
// 	outfile,
// 	d_outfile,
// 	expender
// };

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
	char	*type;
	int		index;
};

struct s_garbage
{
	void		*to_free;
	t_garbage	*next;
};

#endif