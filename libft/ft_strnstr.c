/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:09:37 by mklevero          #+#    #+#             */
/*   Updated: 2025/04/29 18:09:47 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*locates the first occurrence of the null-terminated
string little in the string big,where not more than n characters are
searched. Characters that appear after a '\0' character are not searched.*/

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0])
		return ((char *)big);
	if (!big && !n)
		return (NULL);
	while (big[i] && i < n)
	{
		j = 0;
		while (big[i + j] && little[j] && big[i + j] == little[j] && ((i
					+ j) < n))
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
