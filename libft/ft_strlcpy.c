/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:42:43 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/08 17:46:32 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] > '\0')
	{
		if (dstsize && (i < (dstsize - 1)))
		{
			dst[i] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (i);
}
