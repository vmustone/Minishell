/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:00:58 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/10 17:14:56 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	char	u;

	str = (char *) s;
	u = (char) c;
	if (n == 0)
		return (NULL);
	while (n > 1 && *str != u)
	{
		str++;
		n--;
	}
	if (*str == u)
		return (str);
	else
		return (NULL);
}
