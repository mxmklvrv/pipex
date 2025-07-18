/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:07:49 by mklevero          #+#    #+#             */
/*   Updated: 2025/06/26 20:24:12 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_1;
	size_t	len_2;
	size_t	len_total;
	char	*joined;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	len_total = len_1 + len_2;
	joined = (char *)malloc(sizeof(char) * (len_total + 1));
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, len_total + 1);
	ft_strlcat(joined, s2, len_total + 1);
	return (joined);
}
