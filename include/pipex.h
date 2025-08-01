/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:13:33 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/27 19:29:52 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>     // open
# include <stdbool.h>   // true
# include <stdio.h>     // perror
# include <stdlib.h>    // NULL
# include <sys/types.h> // pid_t
# include <sys/wait.h>  // wait
# include <unistd.h>    // pipe, fork, close, dup2, access, execve

// exit codes
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXEC 126
# define GEN_ERROR 1

// pipe in and out
# define WRITE_TO 1
# define READ_FROM 0

typedef struct s_struct
{
	int		ac;
	char	**av;
	char	**envp;
	int		pipe_fd[2];
	pid_t	pid_one;
	pid_t	pid_two;
	int		infile_fd;
	int		outfile_fd;

}			t_struct;

// main
int			main(int ac, char **av, char **envp);
void		process_child_one(t_struct *data);
void		process_child_two(t_struct *data);
void		redirect_fds(int in_fd, int out_fd);
void		close_pipe_fds(t_struct *data);

// dirs_and_cmds
void		process_cmd(t_struct *data, char *av_cmd);
void		check_abs_rel(char **dir, char **cmd, t_struct *data);
char		**extract_directories(char **envp, char **cmd);
void		check_exec(char **dir, char **cmd, t_struct *data);
char		*get_path(const char *dir, const char *cmd);

// error_and_exit
void		free_mem(char **dir, char **cmd);
void		exit_error(char *msg, char **dir, char **cmd, int exit_code);
void		exit_perror(char **dir, char **cmd, int exit_code);
char		*error_prefix(const char *cmd, bool is_perror);
void		wait_end(t_struct *data);

#endif