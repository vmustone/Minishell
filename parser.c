/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:53:08 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/20 23:01:11 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*last_node(t_exec *head)
{
	t_exec	*temp;

	if (!head)
		return (NULL);
	temp = head;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_exec	*parse_cmd_and_pipes(t_shell *shell, t_exec *head, int r_fd, int w_fd)
{
	t_exec		*node;
	t_tokens	*temp;

	temp = shell->tokens;
	while (temp)
	{
		if (do_pipe_if(temp, head, &r_fd))
			return (parser_close_all_fds(head));
		if (temp->type == T_COMMAND)
		{
			if (head)
				node->next = make_exec_node(temp, shell, r_fd, w_fd);
			if (head)
				node = node->next;
			if (!head)
			{
				head = make_exec_node(temp, shell, r_fd, w_fd);
				node = head;
			}
			reset_fds(&r_fd, &w_fd);
		}
		temp = temp->next;
	}
	return (head);
}

int	set_fds(int *write_fd, int *read_fd, t_tokens *temp, t_shell *shell)
{
	if (temp->type == T_ARROW_L || temp->type == T_ARROW_L_2
		|| temp->type == T_ARROW_R || temp->type == T_ARROW_R_2)
	{
		if (temp->type == T_ARROW_L || temp->type == T_ARROW_L_2)
			*read_fd = set_read_fd(temp, *read_fd, shell);
		else if (temp->type == T_ARROW_R || temp->type == T_ARROW_R_2)
			*write_fd = set_write_fd(temp, *write_fd);
		if (*write_fd == -1 || *read_fd == -1)
			return (1);
	}
	return (0);
}

t_exec	*parse_redirects(t_shell *shell, t_exec *head,
		t_exec *ret, t_tokens *temp)
{
	int			read_fd;
	int			write_fd;

	reset_fds(&read_fd, &write_fd);
	while (temp)
	{
		if (set_fds(&write_fd, &read_fd, temp, shell) == 1)
			return (parser_close_all_fds(head));
		if (temp->type == T_COMMAND && head)
		{
			while (temp && temp->type != T_PIPE)
			{
				if (set_fds(&write_fd, &read_fd, temp, shell) == 1)
					return (parser_close_all_fds(head));
				temp = temp->next;
			}
			fd_do_if(head, read_fd, write_fd);
			reset_fds(&read_fd, &write_fd);
			head = head->next;
		}
		if (temp)
			temp = temp->next;
	}
	return (check_and_return(ret, read_fd, write_fd));
}

t_exec	*parser(t_shell *shell)
{
	t_exec		*head;
	t_tokens	*temp;

	temp = shell->tokens;
	head = parse_cmd_and_pipes(shell, NULL, 0, 1);
	head = parse_redirects(shell, head, head, shell->tokens);
	if (!head)
	{
		return (NULL);
	}
	return (head);
}
