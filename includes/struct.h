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
typedef struct s_env		t_env;
typedef struct s_cmd		t_cmd;

struct	s_cmd
{
	char	**argv;
	int		fd_in;
	int		fd_out;
	t_cmd	*next;
};

struct s_env
{
	char		*env_name;
	char		*value;
	int			declare;
	t_env		*next;
};

struct s_garbage
{
	void		*to_free;
	t_garbage	*next;
};

#endif