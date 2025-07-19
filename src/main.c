/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:28:06 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/19 15:47:02 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
    t_struct data;
    
	if (ac != 5)
		exit_error(ERR_ARG, NULL);
        
    init_struct(&data, ac, av, envp);
    
    if (pipe(data.pipe_fd) == -1)
        exit_error(ERR_PIPE, NULL);
    process_child_one(&data);
    process_child_two(&data);
    close(data.pipe_fd[WRITE_TO]);
    close(data.pipe_fd[READ_FROM]);
}

void process_child_one(t_struct *data)
{
    data->pid_one = fork();
    if(data->pid_one == -1)
    {
        close(data->pipe_fd[WRITE_TO]);
        close(data->pipe_fd[READ_FROM]);
        exit_error(ERR_FORK_1, NULL);
    }
    if(data->pid_one == 0)
    {
        data->infile_fd = open(data->av[1], O_RDONLY);
        if(data->infile_fd < 0)
        {
            close(data->pipe_fd[WRITE_TO]);
            close(data->pipe_fd[READ_FROM]);
            exit_error("infile opening failed", NULL);
        }
        close(data->pipe_fd[READ_FROM]);
        if(dup2(data->infile_fd, STDIN_FILENO) == -1 || dup2(data->pipe_fd[WRITE_TO], STDOUT_FILENO) == -1)
        {
            close(data->infile_fd);
            close(data->pipe_fd[WRITE_TO]);
            exit_error("dup2 failed in chiled one", NULL);
        }
        close(data->infile_fd);
        close(data->pipe_fd[WRITE_TO]);
    }
}

void process_child_two(t_struct *data)
{
    data->pid_two = fork();
    if(data->pid_two == -1)
    {
        close(data->pipe_fd[WRITE_TO]);
        close(data->pipe_fd[READ_FROM]);
        exit_error(ERR_FORK_2, NULL);
    }
    if(data->pid_two == 0)
    {
        data->outfile_fd = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(data->outfile_fd < 0)
        {
            close(data->pipe_fd[WRITE_TO]);
            close(data->pipe_fd[READ_FROM]);
            exit_error("outfile opening failed", NULL);
        }
        close(data->pipe_fd[WRITE_TO]);
        if(dup2(data->pipe_fd[READ_FROM], STDIN_FILENO) == -1 || dup2(data->outfile_fd, STDOUT_FILENO) == -1)
        {
            close(data->outfile_fd);
            close(data->pipe_fd[READ_FROM]);
            exit_error("dup2 failed in chiled two", NULL);
        } 
        close(data->outfile_fd);
        close(data->pipe_fd[READ_FROM]);
    }
}



void init_struct(t_struct *data,int ac, char **av, char **envp)
{
    data->ac = ac;
    data->av = av;
    data->envp = envp;
}

void	exit_error(char *msg, t_struct *data)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
