/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:08:33 by valentin          #+#    #+#             */
/*   Updated: 2022/12/01 00:27:39 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_access(char **paths, char **argv, int argc)
{
	char	**cmd_args;
	int		i;

	i = 0;
	while (i < argc - 3)
	{
		cmd_args = ft_split(argv[2 + i], ' ');
		if (get_cmd_access(paths, cmd_args[0]))
			waitpid(0, NULL, 0);
		child_free2(cmd_args);
		i++;
	}
	return (1);
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

void	child_free2(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args);
}
