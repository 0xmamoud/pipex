/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:18:10 by kane              #+#    #+#             */
/*   Updated: 2024/03/21 15:23:34 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	char	*ft_concat(char *args, char *cmd);
static	int	ft_chr(const char *s, char c);
static	char	*ft_parse_path(char *cmd, char **envp);

char	*ft_path(char *cmd, char **envp)
{
	char	*path;

	if (!cmd)
		return (NULL);
	if (!envp || !*envp)
		path = ft_strdup(cmd);
	else
		path = ft_parse_path(cmd, envp);
	if (!path)
		return (NULL);
	return (path);
}

static	char	*ft_parse_path(char *cmd, char **envp)
{
	char	*path;
	char	**args;

	int (i) = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	args = ft_split(envp[i] + 5, ':');
	if (!args)
		return (NULL);
	i = -1;
	while (args[++i])
	{
		path = ft_concat(args[i], cmd);
		if (!path)
			return (ft_free(args), NULL);
		if (access(path, F_OK) == 0)
		{
			ft_free(args);
			if (ft_chr(path, '.'))
				return (free(path), cmd);
			return (path);
		}
		free(path);
	}
	return (ft_free(args), cmd);
}

static	char	*ft_concat(char *args, char *cmd)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(args, "/");
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!str)
		return (NULL);
	return (str);
}

static	int	ft_chr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
