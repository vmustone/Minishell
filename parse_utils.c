/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:54:33 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 18:23:25 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pipe(t_exec *last)
{
	int		pipe_fd[2];

	if (!last)
	{
		ft_error("syntax error near unexpected token `|'");
		return (-1);
	}
	if (pipe(pipe_fd) == -1)
		return (-1);
	if (last->write_fd == 1)
		last->write_fd = pipe_fd[1];
	return (pipe_fd[0]);
}

void	redir_errors(int error, t_tokens *temp)
{
	if (error == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->next->data, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("error opening fd", 2);
		ft_putstr_fd("\n", 2);
	}
}

t_exec	*check_and_return(t_exec *ret, int read_fd, int write_fd)
{
	if (!ret)
		close_fds(read_fd, write_fd);
	return (ret);
}

void	fd_do_if(t_exec *head, int read_fd, int write_fd)
{
	if (read_fd != 0)
		head->read_fd = parser_set_read_fd(head, read_fd);
	if (write_fd != 1)
		head->write_fd = parser_set_write_fd(head, write_fd);
}

int	do_pipe_if(t_tokens *temp, t_exec *head, int *r_fd)
{
	if (temp->type == T_PIPE)
		*r_fd = do_pipe(last_node(head));
	if (*r_fd == -1)
		return (1);
	return (0);
}
