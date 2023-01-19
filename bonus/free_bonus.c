/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:04:33 by valentin          #+#    #+#             */
/*   Updated: 2023/01/18 18:10:11 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	pipe_free(t_data *data)
{
	close(data->infile);
	close(data->outfile);
	if (data->heredoc)
		unlink(".heredoc_tmp");
	free(data->tube);
	exit(1);
}

void	parent_free(t_data *data)
{
	int	i;

	i = 0;
	free(data->tube);
	if (data->infile >= 0)
		close(data->infile);
	close(data->outfile);
	if (data->heredoc)
		unlink(".heredoc_tmp");
	if (data->cmd_paths == NULL)
		return ;
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
}

void	child_free(char **cmd_args, char *cmd)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args);
	free(cmd);
}

int	free_tab_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != NULL)
	{
		free(str[i++]);
	}
	free(str);
	return (0);
}
