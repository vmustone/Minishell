/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:54:56 by vmustone          #+#    #+#             */
/*   Updated: 2023/08/19 16:21:02 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		ft_putstr_fd("\n", 2);
	}
	else if (signum == SIGQUIT)
	{
		g_exit_status = 131;
		ft_putstr_fd("Quit: 3\n", 2);
	}
}

void	sigint_heredoc(int sig)
{
	char	buf[2];

	(void)sig;
	g_exit_status = 420;
	buf[0] = 4;
	buf[1] = 0;
	ioctl(STDIN_FILENO, TIOCSTI, buf);
}
