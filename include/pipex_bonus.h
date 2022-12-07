/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:39:58 by valentin          #+#    #+#             */
/*   Updated: 2022/12/07 22:19:12 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_data {
	pid_t		pid;
	int			*tube;
	int			infile;
	int			outfile;
	char		*paths;
	char		**cmd_paths;
	int			count;
	int			heredoc;
}				t_data;

char		*find_path(char **envp);
void		close_pipes(t_data *data, int len);
void		parent_free(t_data *data);
void		child_free(char **cmd_args, char *cmd);
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
int			get_next_line(int fd, char **str);
char		*get_next(char *save, int fd);
char		*new_save(char *str);
char		*ft_cut_dest(char *dest);
char		*ft_strjoin1(char *s1, char *s2);
int			check_end(char *dest);
size_t		ft_strlen1(char *s);
int			get_in_out(t_data *data, char **argv, int argc);
int			check_heredoc(char	*str, t_data *data);
void		here_doc(char *argv, t_data *data);

#endif
