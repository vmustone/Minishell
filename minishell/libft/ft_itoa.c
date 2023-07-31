/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:18:19 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/16 15:51:51 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_counter(int n)
{
	int	num;

	num = 0;
	if (n <= 0)
		num++;
	while (n)
	{
		num++;
		n /= 10;
	}
	return (num);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;

	i = num_counter(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[--i] = '0';
	while (n && n < 0)
	{
		str[--i] = ((n % 10) * -1) + 48;
		n /= 10;
	}
	while (n)
	{
		str[--i] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}
