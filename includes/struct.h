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

#endif