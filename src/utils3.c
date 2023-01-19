/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:42:24 by vescaffr          #+#    #+#             */
/*   Updated: 2023/01/18 23:58:57 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	is_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			return (1);
		i++;
	}
	return (0);
}

void	wait_fonct(t_data data)
{
	close_pipes(&data);
	waitpid(0, NULL, 0);
	waitpid(0, NULL, 0);
	parent_free(&data);
}
