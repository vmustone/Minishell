/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:00 by vmustone          #+#    #+#             */
/*   Updated: 2022/11/15 19:19:50 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(const char *s, char c)
{
	size_t	word;

	word = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		while (*s != c && *s != '\0')
		{
			s++;
			if (*s == c || *s == '\0')
				word++;
		}
	}
	return (word);
}

static void	word_size(const char *s, char c, int word, char **new)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (*s != '\0' && word > 0)
	{
		if (*s == c)
			s++;
		if (*s != c)
		{
			size++;
			s++;
			if (*s == c || *s == '\0')
			{
				new[i] = (char *)malloc(sizeof(char) * (size + 1));
				i++;
				size = 0;
				word--;
			}
		}
	}
}

static char	**new_str(const char *s, char c, char **new, size_t word)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*s != '\0' && i < word)
	{
		while (*s == c)
			s++;
		while (*s != c && *s != '\0')
		{
			new[i][j] = *s;
			j++;
			s++;
		}
		new[i][j] = '\0';
		i++;
		j = 0;
	}
	return (new);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	word;

	if (!s)
		return (NULL);
	word = word_counter(s, c);
	new = (char **)malloc(sizeof(char *) * (word + 1));
	if (!new)
		return (NULL);
	new[word] = NULL;
	word_size(s, c, word, new);
	new_str(s, c, new, word);
	return (new);
}
