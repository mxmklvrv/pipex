/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:28:06 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/25 13:39:22 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// input parsing ?

int	main(int ac, char **av, char **envp)
{
	t_struct	data;

	if (ac != 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	data.ac = ac;
    data.av = av;
    data.envp = envp;
	if (pipe(data.pipe_fd) == -1)
		exit_error("Pipe() failed", NULL, NULL, GEN_ERROR);
	process_child_one(&data);
	process_child_two(&data);
	close_pipe_fds(&data);
    wait_end(&data);
}


void	process_child_one(t_struct *data)
{
	data->pid_one = fork();
	if (data->pid_one == -1)
	{
		close_pipe_fds(data);
		exit_perror(NULL, NULL, GEN_ERROR);
	}
	if (data->pid_one == 0)
	{
		data->infile_fd = open(data->av[1], O_RDONLY);
		if (data->infile_fd < 0)
		{
			close_pipe_fds(data);
			exit_perror(NULL, NULL, GEN_ERROR);
		}
		close(data->pipe_fd[READ_FROM]);
		redirect_fds(data->infile_fd, data->pipe_fd[WRITE_TO]);
		process_cmd(data, data->av[2]);
	}
}

void	process_child_two(t_struct *data)
{
	data->pid_two = fork();
	if (data->pid_two == -1)
	{
		close_pipe_fds(data);
		exit_perror(NULL, NULL, GEN_ERROR);
	}
	if (data->pid_two == 0)
	{
		data->outfile_fd = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->outfile_fd < 0)
		{
			close_pipe_fds(data);
			exit_perror(NULL, NULL, GEN_ERROR);
		}
		close(data->pipe_fd[WRITE_TO]);
		redirect_fds(data->pipe_fd[READ_FROM], data->outfile_fd);
		process_cmd(data, data->av[3]);
	}
}

void	redirect_fds(int in_fd, int out_fd)
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		close(in_fd);
		close(out_fd);
		exit_perror(NULL, NULL, GEN_ERROR);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		close(in_fd);
		close(out_fd);
		exit_perror(NULL, NULL, GEN_ERROR);
	}
	close(in_fd);
	close(out_fd);
}
