/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_ft_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:32:28 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/08 19:24:21 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	counter(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && count == 0)
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] != '\0' && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		if (s[i])
			i++;
	}
	return (count);
}

static char	*splitter(char const *s, int len, int count, t_shell *shell)
{
	int		i;
	char	*ret;

	i = 0;
	if (count == 0)
		return (NULL);
	ret = (char *) oh_my_malloc((count +1) * sizeof(char), shell->allocs);
	if (!ret)
		return (NULL);
	while (i < count)
	{
		ret[i] = s[len];
		i++;
		len++;
	}
	ret[i] = '\0';
	return (ret);
}

static int	cremover(char const *s, char c, int i)
{
	while (s[i] == c)
		i++;
	return (i);
}

char	**shell_ft_split(char const *s, char c, t_shell *shell)
{
	char	**ret;
	size_t	i;
	int		retcount;
	int		count;

	if (!s)
		return (NULL);
	retcount = 0;
	i = counter(s, c);
	ret = (char **)oh_my_malloc(sizeof(char *) * (i + 1), shell->allocs);
	i = 0;
	if (!ret)
		return (NULL);
	ret[counter(s, c)] = NULL;
	while (s[i] != '\0')
	{
		count = 0;
		i = cremover(s, c, i);
		while (s[i + count] != c && s[i + count] != '\0')
			count++;
		ret[retcount] = splitter(s, i, count, shell);
		i = i + count;
		retcount++;
	}
	return (ret);
}
