/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:15:17 by valentin          #+#    #+#             */
/*   Updated: 2023/01/19 00:57:35 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

void	close_pipes(t_data *data, int len)
{
	int	i;

	i = 0;
	while (i < (2 * (len - 1)))
		close(data->tube[i++]);
}

void	init(t_data	*data, int argc)
{
	data->infile = 0;
	data->outfile = 0;
	data->tube = malloc(sizeof(int) * (2 * (argc - 3 - 1 - data->heredoc)));
	data->count = 0;
	return ;
}

int	get_in_out(t_data *data, char **argv, int argc)
{
	if (data->heredoc == 1)
	{
		here_doc(argv[2], data);
		data->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		if (data->outfile < 0)
			return (write_perror(argv[argc - 1]));
	}
	else
	{
		data->infile = open(argv[1], O_RDONLY);
		if (data->infile < 0)
			write_perror(argv[1]);
		data->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (data->outfile < 0)
		{
			free(data->tube);
			return (write_perror(argv[argc - 1]));
		}
	}
	return (1);
}
