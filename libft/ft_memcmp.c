/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:27:29 by mklevero          #+#    #+#             */
/*   Updated: 2025/04/29 17:53:39 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*function compares the first n bytes (each interpreted as unsignedchar)
of the memory areas s1 and s2.*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*copy_s1;
	const unsigned char	*copy_s2;
	size_t				i;

	copy_s1 = (const unsigned char *)s1;
	copy_s2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (copy_s1[i] != copy_s2[i])
			return (copy_s1[i] - copy_s2[i]);
		i++;
	}
	return (0);
}
