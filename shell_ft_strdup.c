/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_ft_strdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:33:37 by vmustone          #+#    #+#             */
/*   Updated: 2023/08/03 16:49:14 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_ft_strdup(const char *s1, t_allocations *allocs)
{
	int		i;
	char	*ret;

	i = 0;
	ret = (char *)oh_my_malloc(sizeof(char) * ft_strlen(s1) + 1, allocs);
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
