/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:15:17 by valentin          #+#    #+#             */
/*   Updated: 2023/01/17 23:20:51 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

char	*find_path(char **envp)
{
	if (!is_path(envp))
		return (NULL);
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	close_pipes(t_data *data)
{
	close(data->tube[0]);
	close(data->tube[1]);
}

void	parent_free(t_data *data)
{
	int	i;

	i = 0;
	if (data->infile > 0)
		close(data->infile);
	close(data->outfile);
	if (data->cmd_paths == NULL)
		return ;
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
}

void	child_free(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_args[i])
	{
		free(data->cmd_args[i]);
		i++;
	}
	free(data->cmd_args);
	free(data->cmd);
}
