/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singnals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:26:04 by vmustone          #+#    #+#             */
/*   Updated: 2023/08/21 18:30:53 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_ctrl_c(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	g_exit_status = 1;
}

void	signal_start(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	close_echo(struct termios *ter)
{
	ter->c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, ter);
}

void	reset_echo(struct termios *ter)
{
	ter->c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, ter);
}

void	handle_ctrl_d(void)
{
	printf("exit\n");
	exit (g_exit_status);
}
