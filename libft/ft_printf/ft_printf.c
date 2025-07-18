/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:25:04 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/05 16:09:18 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	pf_check_format(const char *format, va_list *args)
{
	if (*format == 'c')
		return (ftpf_putchar(va_arg(*args, int)));
	else if (*format == 's')
		return (ftpf_putstr(va_arg(*args, char *)));
	else if (*format == '%')
		return (ftpf_putchar('%'));
	else if (*format == 'd' || *format == 'i')
		return (ftpf_putnum(va_arg(*args, int)));
	else if (*format == 'u')
		return (ftpf_putnum_unsigned(va_arg(*args, unsigned int)));
	else if (*format == 'x')
		return (ftpf_base(va_arg(*args, unsigned int), 16, BASE16L));
	else if (*format == 'X')
		return (ftpf_base(va_arg(*args, unsigned int), 16, BASE16U));
	else if (*format == 'p')
		return (ftpf_ptr(va_arg(*args, void *)));
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total;
	int		count;

	if (!format)
		return (-1);
	total = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count = pf_check_format(format, &args);
		}
		else
			count = write(1, format, 1);
		if (count == -1)
			return (va_end(args), -1);
		total += count;
		format++;
	}
	return (va_end(args), total);
}
