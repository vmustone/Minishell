/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:03:20 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/20 21:18:54 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_read_fd(t_tokens *temp, int read_fd, t_shell *shell)
{
	if (read_fd != 0)
		close(read_fd);
	if (temp->type == T_ARROW_L)
	{
		read_fd = open(temp->next->data, O_RDONLY);
		if (read_fd == -1)
		{
			ft_error("Permission denied to open file");
			g_exit_status = 1;
			return (-1);
		}
	}
	if (temp->type == T_ARROW_L_2)
		read_fd = here_doc(temp->next->data, shell);
	return (read_fd);
}

int	set_write_fd(t_tokens *temp, int write_fd)
{
	if (write_fd != 1)
		close(write_fd);
	if (temp->type == T_ARROW_R)
	{
		write_fd = open(temp->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (write_fd == -1)
		{
			ft_error("Permission denied to open file");
			g_exit_status = 1;
			return (-1);
		}
	}
	if (temp->type == T_ARROW_R_2)
	{
		write_fd = open(temp->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (write_fd == -1)
		{
			ft_error("Permission denied to open file");
			g_exit_status = 1;
			return (-1);
		}
	}
	return (write_fd);
}

int	parser_set_read_fd(t_exec *head, int read_fd)
{
	if (head->read_fd != 0)
		close(head->read_fd);
	return (read_fd);
}

int	parser_set_write_fd(t_exec *head, int write_fd)
{
	if (head->write_fd != 1)
		close(head->write_fd);
	return (write_fd);
}

t_exec	*parser_close_all_fds(t_exec *head)
{
	while (head)
	{
		if (head->read_fd != 0)
			close(head->read_fd);
		if (head->write_fd != 1)
			close(head->write_fd);
		head = head->next;
	}
	return (NULL);
}
