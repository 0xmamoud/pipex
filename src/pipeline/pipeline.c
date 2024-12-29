/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:26:20 by mkane             #+#    #+#             */
/*   Updated: 2024/03/21 13:54:54 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static	void	ft_init(t_pipex *pipex, char **argv, int argc)
{
	char	*delimiter;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		delimiter = ft_strjoin(argv[2], "\n");
		if (!delimiter || argc < 6)
			exit(1);
		pipex->here_doc = 1;
		here_doc(delimiter, argv[2]);
		pipex->len_cmd = argc - 4;
		pipex->start = 3;
		pipex->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT \
		| O_APPEND, 0777);
	}
	else
	{
		pipex->here_doc = 0;
		pipex->len_cmd = argc - 3;
		pipex->start = 2;
		pipex->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT \
		| O_TRUNC, 0777);
	}
	pipex->loop_index = 0;
	pipex->fd_in = open(argv[1], O_RDONLY);
}

static	void	ft_close_fd(t_pipex *pipex)
{
	if (pipex->here_doc)
		unlink("here_doc");
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc >= 5)
	{
		ft_init(&pipex, argv, argc);
		while (pipex.loop_index < pipex.len_cmd)
		{
			ft_pipex(&pipex, argv[pipex.loop_index + pipex.start], \
			envp, argv[1]);
			pipex.loop_index++;
		}
		while (wait(NULL) > 0)
			;
		ft_close_fd(&pipex);
	}
	return (0);
}
