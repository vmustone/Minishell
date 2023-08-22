/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:55:59 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/14 15:27:17 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*m;
	size_t	i;
	size_t	strl;

	if (!s)
		return (NULL);
	strl = ft_strlen(s);
	i = 0;
	if (start >= strl)
		len = 0;
	if (len < strl - start)
		m = (char *)malloc(sizeof(char) * len + 1);
	else
		m = (char *)malloc(sizeof(char) * (strl - start + 1));
	if (m == NULL)
		return (NULL);
	while (s[start] != '\0' && i < len && start < strl)
	{
		m[i] = s[start];
		i++;
		start++;
	}
	m[i] = '\0';
	return (m);
}
