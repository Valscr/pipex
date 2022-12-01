/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:08:33 by valentin          #+#    #+#             */
/*   Updated: 2022/12/01 01:57:33 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	check_access(char **paths, char **argv, int argc)
{
	char	**cmd_args;
	int		i;

	i = 0;
	while (i < argc - 3)
	{
		cmd_args = ft_split(argv[2 + i], ' ');
		if (get_cmd_access(paths, cmd_args[0]))
		{
			child_free(cmd_args);
			return (1);
		}
		child_free(cmd_args);
		i++;
	}
	return (0);
}

int	get_cmd_access(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{	
		if (access(cmd, 0) == 0)
			return (1);
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
		{
			free(command);
			return (1);
		}
		free(command);
		paths++;
	}
	return (0);
}
