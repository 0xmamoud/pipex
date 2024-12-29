/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:43:43 by mkane             #+#    #+#             */
/*   Updated: 2024/03/21 15:20:38 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	void	ft_execve(char *argv, char **envp, t_pipex *pipex);
static	void	child_process(t_pipex *pipex, char *argv, char **envp, \
char *path);

void	ft_pipex(t_pipex *pipex, char *argv, char **envp, char *path)
{
	if (pipe(pipex->fd) == -1)
		ft_error(pipex, 1, "Pipe error\n");
	pipex->pid = fork();
	if (pipex->pid == -1)
		ft_error(pipex, 1, "Fork error\n");
	if (pipex->pid == 0)
		child_process(pipex, argv, envp, path);
	else
	{
		close(pipex->fd[1]);
		dup2(pipex->fd[0], STDIN_FILENO);
		close(pipex->fd[0]);
	}
}

static	void	child_process(t_pipex *pipex, char *argv, char **envp, \
char *path)
{
	close(pipex->fd[0]);
	if (pipex->loop_index == 0)
	{
		dup2(pipex->fd_in, STDIN_FILENO);
		if (pipex->fd_in < 0)
		{
			if (access(path, F_OK) == -1)
				ft_error(pipex, 127, "No such file or directory\n");
			ft_error(pipex, 1, "Permission denied\n");
		}
	}
	if (pipex->loop_index == pipex->len_cmd - 1)
	{
		dup2(pipex->fd_out, STDOUT_FILENO);
		if (pipex->fd_out < 0)
			ft_error(pipex, 1, "Permission denied\n");
	}
	else
	{
		dup2(pipex->fd[1], STDOUT_FILENO);
	}
	close(pipex->fd[1]);
	ft_execve(argv, envp, pipex);
}

static	void	ft_execve(char *argv, char **envp, t_pipex *pipex)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd || !*cmd)
	{
		if (cmd)
			ft_free(cmd);
		ft_error(pipex, 1, "Command not found\n");
	}
	path = ft_path(cmd[0], envp);
	if (!path || access(path, F_OK) == -1)
	{
		ft_free(cmd);
		if (!path)
			ft_error(pipex, 127, "No such file or directory\n");
		ft_error(pipex, 1, "Command not found\n");
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free(cmd);
		perror("");
		ft_error(pipex, 1, NULL);
	}
}
