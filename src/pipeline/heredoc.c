/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:52:36 by mkane             #+#    #+#             */
/*   Updated: 2024/03/21 15:30:52 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	ft_open(char *delimiter)
{
	int	fd;

	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		free(delimiter);
		exit(1);
	}
	ft_putstr_fd("> ", 1);
	return (fd);
}

static	void	ft_handle_lim_on_hold(char **lim_on_hold, \
char **line, char *delimiter)
{
	*lim_on_hold = ft_strjoin(*lim_on_hold, *line);
	if (!lim_on_hold)
	{
		free(delimiter);
		free(*line);
		exit(1);
	}
	free(*line);
	*line = *lim_on_hold;
	*lim_on_hold = NULL;
}

static	void	ft_close(char *delimiter, int fd, char **line)
{
	free(delimiter);
	while (*line)
	{
		free(*line);
		*line = get_next_line(fd);
	}
	close(fd);
}

void	here_doc(char *delimiter, char *argv)
{
	char	*line;

	char *(lim_on_hold) = NULL;
	int (fd) = ft_open(delimiter);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			continue ;
		if (lim_on_hold && line)
			ft_handle_lim_on_hold(&lim_on_hold, &line, delimiter);
		if (ft_strncmp(line, argv, ft_strlen(line)) == 0)
		{
			lim_on_hold = argv;
			free(line);
			continue ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		if (ft_strchr(line, '\n'))
			ft_putstr_fd("> ", 1);
		ft_putstr_fd(line, fd);
		free(line);
	}
	ft_close(delimiter, fd, &line);
}
