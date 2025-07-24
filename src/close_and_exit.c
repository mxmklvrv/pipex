/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:05:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/24 17:41:07 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe_fds(t_struct *data)
{
	close(data->pipe_fd[WRITE_TO]);
	close(data->pipe_fd[READ_FROM]);
}

void	free_mem(char **dir, char **cmd)
{
	if (dir)
		free_sp(dir);
	if (cmd)
		free_sp(cmd);
}

void	exit_error(char *msg, char **dir, char **cmd, int exit_code)
{
	free_mem(dir, cmd);
	if (exit_code == GEN_ERROR || exit_code == CMD_NOT_EXEC)
		perror(msg);
	else
		ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_code);
}
