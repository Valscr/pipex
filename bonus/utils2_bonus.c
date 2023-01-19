/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:23:11 by valentin          #+#    #+#             */
/*   Updated: 2023/01/18 19:22:50 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	is_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd == NULL || cmd[0] == 0)
		return (0);
	if (access(cmd, 0) == 0)
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

int	check_error(char **argv, t_data *data, int argc)
{
	char	**dest;
	int		i;
	int		j;

	j = 2 + data->heredoc;
	i = 0;
	while (j <= (argc - 2))
	{
		dest = ft_split(argv[j], ' ');
		if (!is_cmd(data->cmd_paths, dest[0]))
			i++;
		free_tab_str(dest);
		j++;
	}
	if (open(argv[1], O_RDONLY) < 0 && data->heredoc == 0)
		i++;
	if (i > 0)
		return (1);
	return (0);
}
