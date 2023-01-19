/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:39:58 by valentin          #+#    #+#             */
/*   Updated: 2023/01/19 00:06:24 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

typedef struct s_data {
	pid_t		pid1;
	pid_t		pid2;
	int			tube[2];
	int			infile;
	int			outfile;
	int			file;
	char		**str;
	char		**str2;
	char		**cmd_args;
	char		*cmd;
	char		*paths;
	char		**cmd_paths;
}				t_data;

char		*find_path(char **envp);
void		close_pipes(t_data *data);
void		parent_free(t_data *data);
void		child_free(t_data *data);
char		*get_cmd(char **paths, char *cmd);
void		first_child(t_data data, char *argv[], char *envp[]);
void		second_child(t_data data, char *argv[], char *envp[]);
int			write_error(char *str);
int			write_perror(char *str);
int			free_tab_str(char **str);
int			check_return(int i);
int			check_error(char **argv, t_data *data);
int			open_file(char **argv, t_data *data, int argc);
int			is_cmd(char **paths, char *cmd);
int			is_path(char **envp);
void		wait_fonct(t_data data);

#endif
