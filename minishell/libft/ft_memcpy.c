/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:46:11 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/14 13:54:54 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*c;

	s = (char *) src;
	c = dst;
	if (c == NULL && s == NULL)
		return (NULL);
	while (n > 0)
	{
		*c = *s;
		s++;
		c++;
		n--;
	}
	return (dst);
}
