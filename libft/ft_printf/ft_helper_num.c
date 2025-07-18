/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:00:05 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/05 16:05:00 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ftpf_putnum(long n)
{
	int		i;
	int		check;
	char	res;

	i = 0;
	if (n < 0)
	{
		if (ftpf_putchar('-') < 0)
			return (-1);
		i++;
		n = -n;
	}
	if (n >= 10)
	{
		check = ftpf_putnum(n / 10);
		if (check < 0)
			return (-1);
		i += check;
	}
	res = (n % 10) + '0';
	if (write(1, &res, 1) < 0)
		return (-1);
	i++;
	return (i);
}

int	ftpf_putnum_unsigned(unsigned int n)
{
	int		i;
	int		check;
	char	res;

	i = 0;
	if (n >= 10)
	{
		check = ftpf_putnum_unsigned(n / 10);
		if (check < 0)
			return (-1);
		i += check;
	}
	res = (n % 10) + '0';
	if (write(1, &res, 1) < 0)
		return (-1);
	i++;
	return (i);
}

int	ftpf_base(unsigned long n, unsigned long base, char *str)
{
	int	i;
	int	check;
	int	index;

	i = 0;
	if (n > base - 1)
	{
		check = ftpf_base(n / base, base, str);
		if (check < 0)
			return (-1);
		i += check;
	}
	index = n % base;
	if (write(1, &str[index], 1) < 0)
		return (-1);
	i++;
	return (i);
}

int	ftpf_ptr(void *ptr)
{
	int	ox;
	int	address;

	if (!ptr)
		return (ftpf_putstr("(nil)"));
	ox = write(1, "0x", 2);
	address = ftpf_base((unsigned long)ptr, 16, BASE16L);
	if (ox == -1 || address == -1)
		return (-1);
	return (ox + address);
}
