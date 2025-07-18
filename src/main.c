/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:28:06 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/18 20:21:04 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid_1;
	pid_t	pid_2;

	if (ac != 5)
		exit_error(ERROR_ARG, NULL);
	if (pipe(pipe_fd) == -1)
		exit_error(ERROR_PIPE, NULL);
}

void	exit_error(char *msg, t_struct *data)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}