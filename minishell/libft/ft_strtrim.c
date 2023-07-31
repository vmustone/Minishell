/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:09:08 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/08 17:38:57 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, char *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*new;

	if (!s1)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] != '\0' && check_set(s1[start], (char *)set))
		start++;
	while (end > start && check_set(s1[end - 1], (char *)set))
		end--;
	new = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!new)
		return (NULL);
	while (start <= end)
		new[i++] = s1[start++];
	new[i -1] = '\0';
	return (new);
}
