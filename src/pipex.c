/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:22:18 by vescaffr          #+#    #+#             */
/*   Updated: 2022/12/01 00:22:58 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	write_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (0);
}

int	write_perror(char *str)
{
	perror(str);
	return (0);
}

void	first_child(t_data data, char *argv[], char *envp[])
{
	dup2(data.tube[1], 1);
	close(data.tube[0]);
	dup2(data.infile, 0);
	data.cmd_args = ft_split(argv[2], ' ');
	data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
	if (!data.cmd)
	{
		if (argv[2][0] != '\0')
			write_error(data.cmd_args[0]);
		write_error(": command not found\n");
		child_free(&data);
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
			write_error(data.cmd_args[0]);
		write_error(": command not found\n");
		child_free(&data);
		exit(1);
	}
	execve(data.cmd, data.cmd_args, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc != 5)
		return (write_error("Invalid number of arguments.\n"));
	data.infile = open(argv[1], O_RDONLY);
	if (data.infile < 0)
		return (write_perror(argv[1]));
	data.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (data.outfile < 0)
		return (write_error("Outfile error"));
	if (pipe(data.tube) < 0)
		return (write_error("Error\n"));
	data.paths = find_path(envp);
	data.cmd_paths = ft_split(data.paths, ':');
	data.pid1 = fork();
	if (data.pid1 == 0)
		first_child(data, argv, envp);
	data.pid2 = fork();
	if (data.pid2 == 0)
		second_child(data, argv, envp);
	close_pipes(&data);
	check_access(data.cmd_paths, argv, argc);
	parent_free(&data);
	return (0);
}
