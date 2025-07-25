/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:05:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/25 19:14:56 by mklevero         ###   ########.fr       */
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

void	exit_perror(char **dir, char **cmd, int exit_code)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (cmd && cmd[0])
	{
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	perror(NULL);
	free_mem(dir, cmd);
	exit(exit_code);
}

void	exit_error(char *msg, char **dir, char **cmd, int exit_code)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (cmd && cmd[0])
	{
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	free_mem(dir, cmd);
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
