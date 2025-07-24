/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:05:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/24 20:32:27 by mklevero         ###   ########.fr       */
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
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (exit_code == GEN_ERROR || exit_code == CMD_NOT_EXEC)
		perror(msg);
	else
		ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_code);
}

void	wait_end(t_struct *data)
{
	pid_t	which_pid;
	int		i;
	int		status;
	int		final_status;

	i = 0;
	while (i < 2)
	{
		which_pid = waitpid(-1, &status, 0);
		if (which_pid == -1)
		{
			ft_putendl_fd("waitpid fails", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		else if (which_pid == data->pid_two)
			final_status = status;
		i++;
	}
	if (WIFEXITED(final_status))
		exit(WEXITSTATUS(final_status));
	else
		exit(EXIT_FAILURE);
}
