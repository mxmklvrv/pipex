/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:42:16 by mklevero          #+#    #+#             */
/*   Updated: 2025/04/28 20:53:20 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_of_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*sep_words(char const *s, char c)
{
	char	*sep;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	sep = (char *)malloc(sizeof(char) * (i + 1));
	if (sep == NULL)
		return (NULL);
	while (i > j)
	{
		sep[j] = s[j];
		j++;
	}
	sep[j] = '\0';
	return (sep);
}

static void	*free_sp(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return (NULL);
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		j;

	j = 0;
	if (s == NULL)
		return (NULL);
	arr = malloc(sizeof(char *) * (number_of_words(s, c) + 1));
	if (arr == NULL)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			arr[j] = sep_words(s, c);
			if (!arr[j++])
				return (free_sp(arr));
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	arr[j] = NULL;
	return (arr);
}
