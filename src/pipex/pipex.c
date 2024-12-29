/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:00:03 by mkane             #+#    #+#             */
/*   Updated: 2024/03/21 13:40:46 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static	void	ft_init(t_pipex *pipex, char **argv, int argc)
{
	pipex->len_cmd = argc - 3;
	pipex->loop_index = 0;
	pipex->here_doc = 0;
	pipex->fd_in = open(argv[1], O_RDONLY);
	pipex->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
}

static	void	ft_close_fd(t_pipex *pipex)
{
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc == 5)
	{
		ft_init(&pipex, argv, argc);
		while (pipex.loop_index < pipex.len_cmd)
		{
			ft_pipex(&pipex, argv[pipex.loop_index + 2], envp, argv[1]);
			pipex.loop_index++;
		}
		while (wait(NULL) > 0)
			;
		ft_close_fd(&pipex);
	}
	return (0);
}
