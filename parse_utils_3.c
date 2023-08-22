/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:11:33 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/20 21:01:46 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes_and_dollar(char *data, int remove_dollar, t_shell *shell)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = oh_my_malloc(ft_strlen(data) + 2, shell->allocs);
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '\"')
			i++;
		else if (data[i] == '$' && remove_dollar)
			i++;
		else
			ret[j++] = data[i++];
	}
	if (remove_dollar && ft_strcmp(ret, "?"))
	{
		ret[j] = '=';
		ret[j + 1] = '\0';
	}
	else
		ret[j] = '\0';
	return (ret);
}

int	is_single_quoted(char *data)
{
	int			i;
	char		quote;

	i = 0;
	if (data[0] != '\'' && data[0] != '\"')
		return (0);
	while (data[i] && data[i] != '$')
		i++;
	if (data[i] == '$')
	{
		quote = data[i - 1];
		i++;
		while (data[i] && data[i] != quote)
			i++;
		if (data[i] == quote && quote == '\'')
			return (1);
	}
	return (0);
}

char	*make_expand(char *data, char *var, t_shell *shell)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = oh_my_malloc(ft_strlen(data) + ft_strlen(var) + 1, shell->allocs);
	while (data[i] && data[i] != '=')
		i++;
	i++;
	while (data[i])
		ret[j++] = data[i++];
	ret[j] = '\0';
	return (ret);
}

void	reset_fds(int *read_fd, int *write_fd)
{
		*read_fd = 0;
		*write_fd = 1;
}

void	close_fds(int read_fd, int write_fd)
{
	if (read_fd != 0)
		close(read_fd);
	if (write_fd != 1)
		close(write_fd);
}
