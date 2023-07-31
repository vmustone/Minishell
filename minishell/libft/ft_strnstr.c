/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:00:52 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/14 14:55:04 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*n;
	char	*h;
	size_t	i;

	n = (char *) needle;
	h = (char *) haystack;
	i = len;
	while (i > 0 && *h != '\0' && *n != '\0')
	{
		if (*h == *n)
		{
			h++;
			n++;
			i--;
		}
		else
			return (ft_strnstr(haystack + 1, needle, len - 1));
	}
	if (*n == '\0')
		return ((char *)haystack);
	return (NULL);
}
