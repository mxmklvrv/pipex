/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:23:49 by mklevero          #+#    #+#             */
/*   Updated: 2025/04/29 17:54:00 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*copies n bytes from memory area src to memory area dest.
The memory areas must not overlap.*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*copy_dest;
	const unsigned char	*copy_src;
	size_t				i;

	copy_dest = (unsigned char *)dest;
	copy_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		copy_dest[i] = copy_src[i];
		i++;
	}
	return (dest);
}
