/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:22:18 by vescaffr          #+#    #+#             */
/*   Updated: 2023/01/18 23:59:07 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	write_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}

int	write_perror(char *str)
{
	perror(str);
	return (1);
}

void	first_child(t_data data, char *argv[], char *envp[])
{
	if (data.infile < 0)
	{
		parent_free(&data);
		exit (1);
	}
	dup2(data.tube[1], 1);
	close(data.tube[0]);
	dup2(data.infile, 0);
	data.cmd_args = ft_split(argv[2], ' ');
	data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
	if (!data.cmd)
	{
		if (argv[2][0] != '\0')
			write(2, data.cmd_args[0], ft_strlen(data.cmd_args[0]));
		write(2, ": command not found\n", 21);
		child_free(&data);
		parent_free(&data);
		exit(1);
	}
	execve(data.cmd, data.cmd_args, envp);
}

void	second_child(t_data data, char *argv[], char *envp[])
{
	dup2(data.tube[0], 0);
	close(data.tube[1]);
	dup2(data.outfile, 1);
	data.cmd_args = ft_split(argv[3], ' ');
	data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
	if (!data.cmd)
	{
		if (argv[3][0] != '\0')
			write(2, data.cmd_args[0], ft_strlen(data.cmd_args[0]));
		write(2, ": command not found\n", 21);
		child_free(&data);
		parent_free(&data);
		exit(1);
	}
	execve(data.cmd, data.cmd_args, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		i;

	if (argc != 5)
		return (write_error("Invalid number of arguments.\n"));
	if (open_file(argv, &data, argc))
		return (1);
	if (pipe(data.tube) < 0)
		return (write_error("Error\n"));
	data.paths = find_path(envp);
	if (data.paths != NULL)
		data.cmd_paths = ft_split(data.paths, ':');
	else
		data.cmd_paths = NULL;
	i = check_error(argv, &data);
	data.pid1 = fork();
	if (data.pid1 == 0)
		first_child(data, argv, envp);
	data.pid2 = fork();
	if (data.pid2 == 0)
		second_child(data, argv, envp);
	wait_fonct(data);
	return (i);
}
