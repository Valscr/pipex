/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:06:12 by valentin          #+#    #+#             */
/*   Updated: 2022/11/30 22:53:47 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	write_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		write(2, &str[i++], 1);
	return (0);
}

int	write_perror(char *str)
{
	perror(str);
	return (0);
}
