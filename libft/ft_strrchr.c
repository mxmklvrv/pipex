/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:44:00 by mklevero          #+#    #+#             */
/*   Updated: 2025/04/29 18:14:20 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns a pointer to the last occurrence of c in in S.
If c == \0, returns a pointer to \0.*/

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	ch;

	ch = (unsigned char)c;
	len = 0;
	while (s[len])
		len++;
	while (len >= 0)
	{
		if ((unsigned char)s[len] == ch)
			return ((char *)&s[len]);
		len--;
	}
	return (NULL);
}
