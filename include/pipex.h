/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:13:33 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/19 15:48:24 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

// error msg
# define ERR_ARG "Error: Incorrect number of arguments."
# define ERR_PIPE "Error: Pipe() failed."
# define ERR_FORK_1 "Error: Fork one failed."
# define ERR_FORK_2 "Error: Fork two failed."

// pipe in and out
# define WRITE_TO 1
# define READ_FROM 0

typedef struct s_struct
{
	int		ac;
	char	**av;
    char    *envp;
    int     pipe_fd[2];
    pid_t   pid_one;
    pid_t   pid_two;
    int     infile_fd;
    int     outfile_fd;
    
    
    
}			t_struct;

// main
int			main(int ac, char **av, char **envp);

// init
void init_struct(t_struct *data,int ac, char **av, char **envp);

// chiled processing
void process_child_one(t_struct *data);
void process_child_two(t_struct *data);

// exit 
void		exit_error(char *msg, t_struct *data);

#endif