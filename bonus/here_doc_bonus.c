/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:10:16 by valentin          #+#    #+#             */
/*   Updated: 2022/12/07 22:18:56 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	check_heredoc(char	*str, t_data *data)
{
	char	*heredoc;
	int		i;

	i = 0;
	heredoc = malloc(sizeof(char) * 9);
	heredoc = "here_doc\0";
	data->heredoc = 0;
	while (str[i] != '\0')
	{
		if (str[i] != heredoc[i])
			return (0);
		i++;
	}
	data->heredoc++;
	return (1);
}

void	here_doc(char *argv, t_data *data)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		return ;
	while (1)
	{
		write(1, "heredoc> ", 9);
		if (get_next_line(0, &buf) < 0)
			exit(1);
		if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	data->infile = open(".heredoc_tmp", O_RDONLY);
	if (data->infile < 0)
	{
		unlink(".heredoc_tmp");
		return ;
	}
}
