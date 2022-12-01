/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:39:58 by valentin          #+#    #+#             */
/*   Updated: 2022/12/01 01:47:09 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

typedef struct s_data {
	pid_t		pid;
	int			*tube;
	int			infile;
	int			outfile;
	char		*paths;
	char		**cmd_paths;
	int			count;
}				t_data;

char		*find_path(char **envp);
void		close_pipes(t_data *data, int len);
void		parent_free(t_data *data);
void		child_free(char **cmd_args);
char		*get_cmd(char **paths, char *cmd);
int			get_pipes(t_data *data, int argc);
void		get_dup2(int in, int out);
int			loop_pipe(t_data data, char *argv[], char *envp[], int argc);
void		child(t_data *data, char **argv, char *envp[]);
void		init(t_data	*data, int argc);
int			write_error(char *str);
int			write_perror(char *str);
void		pipe_free(t_data *data);
int			check_access(char **paths, char **argv, int argc);
int			get_cmd_access(char **paths, char *cmd);

#endif
