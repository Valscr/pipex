/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:04:33 by valentin          #+#    #+#             */
/*   Updated: 2022/12/07 21:47:33 by valentin         ###   ########.fr       */
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
	if (data->tube)
		free(data->tube);
	close(data->infile);
	close(data->outfile);
	if (data->heredoc)
		unlink(".heredoc_tmp");
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
