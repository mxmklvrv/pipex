/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:48:33 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/18 14:21:07 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*g_leftovers;

char	*ft_get_line(int fd, char *buffer)
{
	ssize_t	byte_was_read;
	char	*tmp;

	byte_was_read = 1;
	while (byte_was_read > 0)
	{
		byte_was_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_was_read <= 0)
			break ;
		buffer[byte_was_read] = '\0';
		if (!g_leftovers)
			g_leftovers = gnl_ft_strdup("");
		tmp = g_leftovers;
		g_leftovers = gnl_ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (gnl_ft_strchr(buffer, '\n'))
			break ;
	}
	if (byte_was_read < 0)
		return (free_and_null());
	return (g_leftovers);
}

char	*ft_save_leftovers(char *full_line)
{
	char	*remainings;
	char	*ptr_nl;

	ptr_nl = gnl_ft_strchr(full_line, '\n');
	if (ptr_nl)
	{
		remainings = gnl_ft_strdup(ptr_nl + 1);
		if (!remainings || *remainings == '\0')
		{
			free(remainings);
			remainings = NULL;
			return (NULL);
		}
		*(ptr_nl + 1) = '\0';
		return (remainings);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	*result;
	char	*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	result = NULL;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free_and_null());
	g_leftovers = ft_get_line(fd, buffer);
	free(buffer);
	buffer = NULL;
	if (!g_leftovers)
		return (free_and_null());
	result = g_leftovers;
	g_leftovers = ft_save_leftovers(result);
	return (result);
}

// function to be called from caller
// to free any leftowers remaining
void	gnl_clear(void)
{
	if (g_leftovers)
	{
		free(g_leftovers);
		g_leftovers = NULL;
	}
}

char	*free_and_null(void)
{
	if (g_leftovers)
	{
		free(g_leftovers);
		g_leftovers = NULL;
	}
	return (NULL);
}
