/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:01:16 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/04 18:42:43 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_redirect_error(int token)
{
	if (token == 1)
		ft_error("minishell: syntax error near unexpected token `<'");
	else if (token == 2)
		ft_error("minishell: syntax error near unexpected token `>'");
	else if (token == 3)
		ft_error("minishell: syntax error near unexpected token `|'");
	return (-1);
}

int	handle_redirect_errors(char *str, int i)
{
	char	token;

	if (str[i] == '<')
		token = '>';
	if (str[i] == '>')
		token = '<';
	if (str[i + 1] == token)
	{
		ft_error("minishell: syntax error near unexpected token `>'");
		return (-1);
	}
	return (i + 1);
}

int	pipes_and_redirections(char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
	{
		if (str[i + 2] == '<' || str[i + 2] == '>' || str[i + 2] == '|')
			return (pipe_redirect_error(1));
		return (i + 2);
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		if (str[i + 2] == '>' || str[i + 2] == '<' || str[i + 2] == '|')
			return (pipe_redirect_error(2));
		return (i + 2);
	}
	else if (str[i] == '<' || str[i] == '>')
		return (handle_redirect_errors(str, i));
	else if (str[i] == '|')
	{
		if (str[i + 1] == '|')
			return (pipe_redirect_error(3));
		return (i + 1);
	}
	return (0);
}
