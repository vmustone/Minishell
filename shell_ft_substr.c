/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_ft_substr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:55:59 by vmustone          #+#    #+#             */
/*   Updated: 2023/08/04 16:33:44 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_ft_substr(char *s, int start, int len, t_allocations *allocs)
{
	char		*m;
	int			i;
	int			strl;

	if (!s)
		return (NULL);
	strl = ft_strlen(s);
	i = 0;
	if (start >= strl)
		len = 0;
	if (len < strl - start)
		m = (char *)oh_my_malloc(sizeof(char) * len + 1, allocs);
	else
		m = (char *)oh_my_malloc(sizeof(char) * (strl - start + 1), allocs);
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
