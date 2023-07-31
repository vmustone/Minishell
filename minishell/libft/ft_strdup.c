/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:33:37 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/08 17:40:22 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ret;

	i = 0;
	ret = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (ret == NULL)
		return (0);
	while (*s1 != '\0')
	{
		ret[i] = *s1;
		i++;
		s1++;
	}
	ret[i] = '\0';
	return (ret);
}
