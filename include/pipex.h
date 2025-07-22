/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:13:33 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/22 17:00:11 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define cmd_not_found 127
# define cmd_not_exec 126 
# define gen_err 1


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

// init
void		init_struct(t_struct *data, int ac, char **av, char **envp);

// child processing
void		process_child_one(t_struct *data);
void		process_child_two(t_struct *data);

// path&cmd exec
void		process_cmd(t_struct *data, char *av_cmd);
void		check_exec(char **dir, char **cmd, t_struct *data);
char		*get_path(const char *dir, const char *cmd);
char		**extract_directories(char **envp, t_struct *data);
void		redirect_fds(int in_fd, int out_fd, t_struct *data);
void		check_abs_rel(char **dir, char **cmd, t_struct *data);

// free, close, exit
void		exit_error(char *msg, char **dir, char **cmd, int);
void		free_mem(char **dir, char **cmd);
void		close_pipe_fds(t_struct *data);

#endif