/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:28:06 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/21 13:09:11 by mklevero         ###   ########.fr       */
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
        process_cmd(data, data->av[2]);
    }
}

void    process_cmd(t_struct *data, char *av_cmd)
{
    char **dir; // needs to free
    char **cmd; // needs to free
    dir = NULL;
    cmd = NULL;
    dir = extract_directories(data->envp, data); // might be NULL 
    cmd = ft_split(av_cmd, ' ');
    if(cmd == NULL)
    {
        free_sp(dir);
        exit_error("CMD splitting failed", data);
    }
    check_exec(dir, cmd, data);
    
}

void    check_exec(char **dir, char **cmd, t_struct *data)
{
    int i;
    char *path;
    
    i = 0;
    while(dir[i])
    {
        path = get_path(dir[i], cmd[0]); // might get NULL 
        if (path == NULL)
        {
            free_sp(dir);
            free_sp(cmd);
            exit_error("Malloc failed in get_path", data);
        }
        if (access(path, X_OK) == 0)
        {
            if(execve(path,cmd, data->envp) == -1)
            {
                free(path);
                free_sp(dir);
                free_sp(cmd);
                exit_error("execve failed", data);
            }
            
        }
        free(path);
        i++;
    }
    free_sp(dir);
    free_sp(cmd);
    exit_error("CMD not found", data);
}

char *get_path(const char *dir, const char *cmd)
{
    char *tmp;
    char *joined_path;
    
    tmp = ft_strjoin(dir, "/");
    if (tmp == NULL)
        return (NULL);
    joined_path = ft_strjoin(tmp, cmd);
    free(tmp);
    if (joined_path == NULL)
        return (NULL);
    return (joined_path);
}



char **extract_directories(char **envp, t_struct *data)
{
    int i;
    char *path;
    char **dir;

    i = 0;
    path = NULL;
    dir = NULL;
    while(envp[i])
    {
        if(ft_strncmp(envp[i], "PATH=", 5) == 0)
            path = envp[i] + 5;
        i++;
    }
    if(path == NULL)
        return (NULL); // for now, not sure 
    dir = ft_split(path, ':');
    if(dir == NULL)
        exit_error("Path splitting failed", data);
    return (dir);
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
        process_cmd(data, data->av[3]);
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
