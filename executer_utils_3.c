/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:02:05 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 17:56:40 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_exec *head, t_shell *shell, int org_write, int org_read)
{
	signal(SIGQUIT, SIG_DFL);
	if (dup_fds(head, org_write, org_read))
	{
		oh_my_free(shell->allocs);
		exit (1);
	}
	close_all_fds(shell, org_write, org_read);
	if (!ft_strncmp(head->cmd, "exit", 4))
	{
		ft_exit(head->argv, shell->allocs);
	}
	if (execute_command(head, shell))
	{
		oh_my_free(shell->allocs);
		exit (1);
	}
	oh_my_free(shell->allocs);
	exit (0);
}
