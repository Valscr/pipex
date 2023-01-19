/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:29:02 by vescaffr          #+#    #+#             */
/*   Updated: 2023/01/19 13:28:12 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_return(int i)
{
	if (i > 0)
		return (1);
	return (0);
}

int	check_error(char **argv, t_data *data)
{
	char	**dest;
	int		i;

	i = 0;
	dest = ft_split(argv[2], ' ');
	if (!is_cmd(data->cmd_paths, dest[0]))
		i++;
	free_tab_str(dest);
	dest = ft_split(argv[3], ' ');
	if (!is_cmd(data->cmd_paths, dest[0]))
		i++;
	free_tab_str(dest);
	if (open(argv[1], O_RDONLY) < 0)
		i++;
	return (check_return(i));
}

int	open_file(char **argv, t_data *data, int argc)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile < 0)
		write_perror(argv[1]);
	data->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (data->outfile < 0)
		return (write_error("Outfile error"));
	return (0);
}

int	is_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd == NULL || cmd[0] == 0)
		return (0);
	if (access(cmd, X_OK) == 0)
		return (1);
	if (paths == NULL)
		return (0);
	while (*paths)
	{
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

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd == NULL)
		return (NULL);
	if (access(cmd, 0) == 0)
		return (cmd);
	if (paths == NULL)
		return (NULL);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}
