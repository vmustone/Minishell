/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:58:22 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/10 18:06:57 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dst && dstsize < ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	while (dst && *dst != '\0' && dstsize > i)
	{	
		dst++;
		i++;
	}
	while (*src != '\0')
	{
		i++;
		if (dstsize > i)
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	if (dst)
		*dst = '\0';
	return (i);
}
