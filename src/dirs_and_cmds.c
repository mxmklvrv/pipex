/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs_and_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:03:24 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/25 13:37:11 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_cmd(t_struct *data, char *av_cmd)
{
	char	**dir;
	char	**cmd;

	dir = NULL;
	cmd = NULL;
	cmd = ft_split(av_cmd, ' ');
	if (cmd == NULL)
		exit_error("CMD splitting failed", dir, cmd, GEN_ERROR);
	if (cmd[0] == NULL)
		exit_error("command not found", dir, cmd, CMD_NOT_FOUND);
	check_abs_rel(NULL, cmd, data);
	dir = extract_directories(data->envp, cmd);
	check_exec(dir, cmd, data);
}

void	check_abs_rel(char **dir, char **cmd, t_struct *data)
{
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) != 0)
			exit_perror(dir, cmd, CMD_NOT_FOUND);
		if (access(cmd[0], X_OK) != 0)
			exit_perror(dir, cmd, CMD_NOT_EXEC);
		if (execve(cmd[0], cmd, data->envp) == -1)
			exit_perror(dir, cmd, CMD_NOT_EXEC);
	}
}

char	**extract_directories(char **envp, char **cmd)
{
	int		i;
	char	*path;
	char	**dir;

	i = 0;
	path = NULL;
	dir = NULL;
	if (envp)
	{
		while (envp[i])
		{
			if (ft_strncmp(envp[i], "PATH=", 5) == 0)
				path = envp[i] + 5;
			i++;
		}
	}
	if (path == NULL)
		exit_error("No such file or directory", NULL, cmd, CMD_NOT_FOUND);
	dir = ft_split(path, ':');
	if (dir == NULL)
		exit_error("Path splitting failed", NULL, cmd, GEN_ERROR);
	return (dir);
}

void	check_exec(char **dir, char **cmd, t_struct *data)
{
	int		i;
	char	*path;

	i = 0;
	while (dir[i])
	{
		path = get_path(dir[i], cmd[0]);
		if (path == NULL)
			exit_error("Malloc failed in get_path", dir, cmd, GEN_ERROR);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) != 0)
			{
				free(path);
				exit_perror(dir, cmd, CMD_NOT_EXEC);
			}
			execve(path, cmd, data->envp);
			free(path);
			exit_perror(dir, cmd, CMD_NOT_EXEC);
		}
		free(path);
		i++;
	}
	exit_error("command not found", dir, cmd, CMD_NOT_FOUND);
}

char	*get_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*joined_path;

	tmp = ft_strjoin(dir, "/");
	if (tmp == NULL)
		return (NULL);
	joined_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (joined_path == NULL)
		return (NULL);
	return (joined_path);
}
