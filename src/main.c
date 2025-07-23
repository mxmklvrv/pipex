/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:28:06 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/23 14:28:59 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// what if no envp
// input parsing ?

int	main(int ac, char **av, char **envp)
{
	t_struct	data;
	int			status1;
	int			status2;

	if (ac != 5)
		exit_error("Incorrect number of arguments.", NULL, NULL, GEN_ERROR);
	init_struct(&data, ac, av, envp);
	if (pipe(data.pipe_fd) == -1)
		exit_error("Pipe() failed.", NULL, NULL, GEN_ERROR);
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


void	process_cmd(t_struct *data, char *av_cmd)
{
	char	**dir;
	char	**cmd;

	dir = NULL;
	cmd = NULL;
	cmd = ft_split(av_cmd, ' ');
	if (cmd == NULL)
		exit_error("CMD splitting failed", NULL, NULL, GEN_ERROR);
	if (cmd[0] == NULL)
		exit_error("Command not found", NULL, NULL, CMD_NOT_FOUND);
    if (data->envp == NULL || data->envp[0] == NULL)
        check_abs_rel(NULL, cmd, data); // check this 
    dir = extract_directories(data->envp, data);
	if (dir == NULL)
		exit_error("Split failed", NULL, cmd, GEN_ERROR);
	check_abs_rel(dir, cmd, data);
	check_exec(dir, cmd, data);
}
// envp below might be null
char	**extract_directories(char **envp, t_struct *data)
{
	int		i;
	char	*path;
	char	**dir;

	i = 0;
	path = NULL;
	dir = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i] + 5;
		i++;
	}
	if (path == NULL)
		exit_error("Path not found in environment", NULL , NULL, GEN_ERROR);
	dir = ft_split(path, ':');
	if (dir == NULL)
		exit_error("Path splitting failed", NULL, NULL, GEN_ERROR);
	return (dir);
}

void	check_abs_rel(char **dir, char **cmd, t_struct *data)
{
	if (cmd[0][0] == '/' || ft_strncmp(cmd[0], "./", 2) == 0)
	{
		if (access(cmd[0], F_OK) != 0)
			exit_error("Command not found", NULL, cmd, CMD_NOT_FOUND);
		if (access(cmd[0], X_OK) != 0)
			exit_error("CMD not executable", NULL, cmd, CMD_NOT_EXEC);
		if (execve(cmd[0], cmd, data->envp) == -1)
			exit_error("execve failed", dir, cmd, GEN_ERROR);
	}
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
		if (access(path, X_OK) == 0)
		{
			if (execve(path, cmd, data->envp) == -1)
			{
				free(path);
				exit_error("CMD not executable", dir, cmd, CMD_NOT_EXEC);
			}
		}
		free(path);
		i++;
	}
	exit_error("Command not found", dir, cmd, CMD_NOT_FOUND);
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


void	init_struct(t_struct *data, int ac, char **av, char **envp)
{
	data->ac = ac;
	data->av = av;
	data->envp = envp;
}
