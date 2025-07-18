/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:49:24 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/16 15:13:40 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*gnl_ft_strdup(const char *s)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*gnl_ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = (unsigned char)c;
	i = 0;
	while ((const unsigned char)s[i] != ch && s[i] != '\0')
		i++;
	if ((const unsigned char)s[i] == ch)
		return ((char *)&s[i]);
	return (NULL);
}

char	*gnl_ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_total;
	char	*joined;
	char	*temp;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_total = ft_strlen(s1) + ft_strlen(s2);
	temp = (char *)malloc(sizeof(char) * (len_total + 1));
	if (temp == NULL)
		return (NULL);
	joined = temp;
	while (*s1)
		*temp++ = *s1++;
	while (*s2)
		*temp++ = *s2++;
	*temp = '\0';
	return (joined);
}
