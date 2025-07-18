/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:27:04 by mklevero          #+#    #+#             */
/*   Updated: 2025/04/29 18:13:54 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*removes chars from set from start and end of s1.
returns a copy of s1.*/

static int	to_trim(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len_t_str;
	char	*t_str;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	start = 0;
	while (s1[start] && to_trim(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && to_trim(s1[end], set))
		end--;
	len_t_str = end - start + 1;
	t_str = (char *)malloc(sizeof(char) * (len_t_str + 1));
	if (t_str == NULL)
		return (NULL);
	ft_strlcpy(t_str, s1 + start, len_t_str + 1);
	return (t_str);
}
