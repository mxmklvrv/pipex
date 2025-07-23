/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:28:06 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/23 19:11:43 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// input parsing ?

int	main(int ac, char **av, char **envp)
{
	t_struct	data;
	int			status1;
	int			status2;

	if (ac != 5)
		exit_error("Incorrect number of arguments", NULL, NULL, GEN_ERROR);
	init_struct(&data, ac, av, envp);
	if (pipe(data.pipe_fd) == -1)
		exit_error("Pipe() failed", NULL, NULL, GEN_ERROR);
	process_child_one(&data);
	process_child_two(&data);
	close_pipe_fds(&data);
	waitpid(data.pid_one, &status1, 0);
	waitpid(data.pid_two, &status2, 0);
	if (WIFEXITED(status2))
		exit(WEXITSTATUS(status2));
	else
		exit(EXIT_FAILURE);
}

void	init_struct(t_struct *data, int ac, char **av, char **envp)
{
	data->ac = ac;
	data->av = av;
	data->envp = envp;
}

void	process_child_one(t_struct *data)
{
	data->pid_one = fork();
	if (data->pid_one == -1)
	{
		close_pipe_fds(data);
		exit_error("Fork one failed.", NULL, NULL, GEN_ERROR);
	}
	if (data->pid_one == 0)
	{
		data->infile_fd = open(data->av[1], O_RDONLY);
		if (data->infile_fd < 0)
		{
			close_pipe_fds(data);
			exit_error("Infile opening failed.", NULL, NULL, GEN_ERROR);
		}
		close(data->pipe_fd[READ_FROM]);
		redirect_fds(data->infile_fd, data->pipe_fd[WRITE_TO], data);
		process_cmd(data, data->av[2]);
	}
}

void	process_child_two(t_struct *data)
{
	data->pid_two = fork();
	if (data->pid_two == -1)
	{
		close_pipe_fds(data);
		exit_error("Fork two failed.", NULL, NULL, GEN_ERROR);
	}
	if (data->pid_two == 0)
	{
		data->outfile_fd = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->outfile_fd < 0)
		{
			close_pipe_fds(data);
			exit_error("Outfile opening failed", NULL, NULL, GEN_ERROR);
		}
		close(data->pipe_fd[WRITE_TO]);
		redirect_fds(data->pipe_fd[READ_FROM], data->outfile_fd, data);
		process_cmd(data, data->av[3]);
	}
}

void	redirect_fds(int in_fd, int out_fd, t_struct *data)
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		close(in_fd);
		close(out_fd);
		exit_error("dup2 failed (stdin)", NULL, NULL, GEN_ERROR);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		close(in_fd);
		close(out_fd);
		exit_error("dup2 failed (stdout)", NULL, NULL, GEN_ERROR);
	}
	close(in_fd);
	close(out_fd);
}
