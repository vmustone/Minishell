/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:26:04 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/31 17:11:12 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static void	handle_ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
static void	handle_ctrl_d(int signum)
{
	(void)signum;
	printf("exit\n");
	exit (1);
}

static void	signal_interrupt(int signum)
{
	(void)signum;
	printf("\n");
}

void	signal_exec(void)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, handle_ctrl_d);
}

void	signal_start(void)
{
	signal(SIGINT, handle_ctrl_c);	
	signal(SIGQUIT, SIG_IGN);
}