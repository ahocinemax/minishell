/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:31:35 by ahocine           #+#    #+#             */
/*   Updated: 2022/08/17 18:31:38 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"
char *  readline (const char *prompt);

void    ft_display_prompt(char *actual_forlder_name)
{
    size_t  len;

    len = 0;
    if (!actual_forlder_name)
        return ;
    while (actual_forlder_name[len])
        len++;
    write(1, actual_forlder_name, len + 1);
    write (1, " -> ", 4);
}

int main(int ac, char **av)
{
    if (ac == 2)
    {
        av++;
        ft_display_prompt(*av);
    }
    return (0);
}