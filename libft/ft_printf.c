/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:37:43 by vmustone          #+#    #+#             */
/*   Updated: 2023/02/28 19:18:54 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	unsigned_integer(unsigned int nbr)
{
	int	ret;

	ret = 0;
	if (nbr > 9)
	{
		ret += ft_putnbr_val(nbr / 10);
		ret += ft_putnbr_val(nbr % 10);
	}
	else
		ret += ft_putchar_val(nbr + '0');
	return (ret);
}

int	hexadecimal_integer(unsigned long long nbr, int caps)
{
	int	ret;

	ret = 0;
	if (nbr <= 9)
		ret += ft_putnbr_val(nbr);
	else if (nbr >= 10 && nbr <= 15 && caps == 0)
		ret += ft_putchar_val(nbr + 87);
	else if (nbr >= 10 && nbr <= 15 && caps == 1)
		ret += ft_putchar_val(nbr + 55);
	else if (nbr >= 16)
	{
		ret += hexadecimal_integer(nbr / 16, caps);
		ret += hexadecimal_integer(nbr % 16, caps);
	}
	return (ret);
}

int	check_specifier(va_list arguments, const char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar_val(va_arg(arguments, int));
	if (c == 's')
		count += ft_putstr_val(va_arg(arguments, char *));
	if (c == 'd' || c == 'i')
		count += ft_putnbr_val(va_arg(arguments, int));
	if (c == 'p')
	{
		count += write(1, "0x", 2);
		count += hexadecimal_integer(va_arg(arguments, unsigned long long), 0);
	}
	if (c == 'u')
		count += unsigned_integer(va_arg(arguments, unsigned int));
	if (c == 'x')
		count += hexadecimal_integer(va_arg(arguments, unsigned int), 0);
	if (c == 'X')
		count += hexadecimal_integer(va_arg(arguments, unsigned int), 1);
	if (c == '%')
		count += ft_putchar_val('%');
	return (count);
}

int	ft_printf(const char *src, ...)
{
	va_list	arguments;
	int		return_value;

	return_value = 0;
	va_start(arguments, src);
	while (*src)
	{
		if (*src == '%')
		{
			src++;
			if (*src == 0)
				break ;
			return_value += check_specifier(arguments, *src);
		}
		else
			return_value += ft_putchar_val(*src);
		src++;
	}
	va_end(arguments);
	return (return_value);
}
