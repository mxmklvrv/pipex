/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:03:05 by mklevero          #+#    #+#             */
/*   Updated: 2025/04/29 19:24:56 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*allocates memory for an array of nmemb elements of size bytes
returns a pointer to the allocated memory.  The memory is set to zero.
checks for overflow.*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	t_bytes;

	t_bytes = nmemb * size;
	if (size != 0 && (t_bytes / size != nmemb))
		return (NULL);
	ptr = malloc(t_bytes);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, (t_bytes));
	return (ptr);
}
