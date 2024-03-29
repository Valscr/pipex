/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:22:18 by vescaffr          #+#    #+#             */
/*   Updated: 2023/01/19 13:23:46 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	child(t_data *data, char **argv, char *envp[])
{
	char	**cmd_args;
	char	*cmd;

	if (data->infile < 0 && data->count == 0)
	{
		parent_free(data);
		exit (1);
	}
	cmd_args = ft_split(argv[2 + data->heredoc + data->count], ' ');
	cmd = get_cmd(data->cmd_paths, cmd_args[0]);
	if (!cmd)
	{
		if (argv[2 + data->count + data->heredoc][0] != '\0')
			write(2, cmd_args[0], ft_strlen(cmd_args[0]));
		write(2, ": command not found\n", 21);
		child_free(cmd_args, cmd);
		parent_free(data);
		exit(1);
	}
	execve(cmd, cmd_args, envp);
}

int	get_pipes(t_data *data, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 4 - data->heredoc)
	{
		if (pipe(data->tube + 2 * i) < 0)
		{
			parent_free(data);
			return (0);
		}
		i++;
	}
	return (1);
}

void	get_dup2(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

int	loop_pipe(t_data data, char *argv[], char *envp[], int argc)
{
	if (!get_pipes(&data, argc))
		return (write_error("Error\n"));
	while (data.count < (argc - 3 - data.heredoc))
	{	
		data.pid = fork();
		if (data.pid == 0)
		{
			if (data.count == 0)
				get_dup2(data.infile, data.tube[1]);
			else if (data.count == (argc - 4 - data.heredoc))
				get_dup2(data.tube[2 * data.count - 2], data.outfile);
			else
				get_dup2(data.tube[2 * data.count - 2],
					data.tube[2 * data.count + 1]);
			close_pipes(&data, argc - 3 - data.heredoc);
			child(&data, argv, envp);
		}
		data.count++;
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		i;
	int		j;

	i = 0;
	if (argc < (5 + check_heredoc(argv[1], &data)))
		return (write_error("Invalid number of arguments\n"));
	init(&data, argc);
	if (!get_in_out(&data, argv, argc))
		return (1);
	data.paths = find_path(envp);
	if (data.paths != NULL)
		data.cmd_paths = ft_split(data.paths, ':');
	else
		data.cmd_paths = NULL;
	j = check_error(argv, &data, argc);
	loop_pipe(data, argv, envp, argc);
	close_pipes(&data, argc - 3 - data.heredoc);
	while (i++ < 2 * (argc - 3 - data.heredoc - 1))
		waitpid(0, NULL, 0);
	parent_free(&data);
	return (j);
}
