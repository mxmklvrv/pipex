/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:05:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/26 12:35:33 by mklevero         ###   ########.fr       */
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
/*
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
*/

void	exit_error(char *msg, char **dir, char **cmd, int exit_code)
{
    char    *prefix;
    char    *error_msg;
    char    *command;
    
    command = NULL; 
	if (cmd && cmd[0])
        command = cmd[0];
    prefix = error_prefix(command);
    if(prefix == NULL)
    {
        free_mem(dir, cmd);
        exit(EXIT_FAILURE);
    }
    error_msg = ft_strjoin(prefix, msg);
    free(prefix);
    if(error_msg == NULL)
    {
        free_mem(dir, cmd);
        exit(EXIT_FAILURE);
    }
	ft_putendl_fd(error_msg, STDERR_FILENO);
    free(error_msg);
	free_mem(dir, cmd);
	exit(exit_code);
}
void	exit_perror(char **dir, char **cmd, int exit_code)
{
    char    *prefix;
    char    *command;
    
    command = NULL;
	if (cmd && cmd[0])
        command = cmd[0];
    prefix = error_prefix(command);
    if(prefix == NULL)
    {
        free_mem(dir, cmd);
        exit(EXIT_FAILURE);
    }
    ft_putstr_fd(prefix, STDERR_FILENO);
    free(prefix);
    perror(NULL);
	free_mem(dir, cmd);
	exit(exit_code);
}

char *error_prefix(const char *cmd)
{
    char *prefix;
    char *tmp;
    
    prefix = ft_strdup("pipex: ");
    if(prefix == NULL)
        return (NULL);
    if (cmd)
    {
        tmp = ft_strjoin(prefix, cmd);
        free(prefix);
        if(tmp == NULL)
            return (NULL);
        prefix = ft_strjoin(tmp, ": ");
        free(tmp);
        if (prefix == NULL)
            return (NULL);
    }
    return (prefix);
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
