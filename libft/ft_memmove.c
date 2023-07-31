/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:17:53 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/14 13:54:38 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*s;
	char		*d;

	i = 0;
	s = (char *) src;
	d = (char *) dst;
	if (d == NULL && s == NULL)
		return (NULL);
	if (d > s)
	{
		while (len > 0)
		{
			len--;
			d[len] = s[len];
		}
	}	
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
