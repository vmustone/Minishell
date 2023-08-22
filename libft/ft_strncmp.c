/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:45:07 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/10 14:59:45 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2 && n > 1)
	{
		str1++;
		str2++;
		n--;
	}
	if (n == 0)
		return (0);
	if (*str1 == *str2)
		return (0);
	return (*str1 - *str2);
}
