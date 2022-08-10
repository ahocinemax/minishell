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
# include <stdlib.h>
# include <fcntl.h>

# define _STD_OUT	1
# define _STD_ERR	2
# define ENV_PATH	""

int		ft_check_path(char *path);
void	ft_echo(char *var);
void	ft_cd(char *str);

#endif