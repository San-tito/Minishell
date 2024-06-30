/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/30 14:17:33 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "input.h"
#include "minishell.h"
#include "sig.h"

void	heredoc_sigint_sighandler(int sig)
{
	signal(sig, heredoc_sigint_sighandler);
	if (*last_exit_value() < 128)
		*last_exit_value() = 128 + SIGINT;
	if (rl_readline_state & RL_STATE_SIGHANDLER)
	{
		ft_putchar_fd(10, 2);
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}

void	sigint_sighandler(int sig)
{
	signal(sig, sigint_sighandler);
	if (*last_exit_value() < 128)
		*last_exit_value() = 128 + SIGINT;
	if (rl_readline_state & RL_STATE_SIGHANDLER)
	{
		ft_putchar_fd(10, 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	enable_document_interrupt(void)
{
	*last_exit_value() = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_sigint_sighandler);
}

void	reset_terminating_signals(void)
{
	signal(SIGQUIT, NULL_HANDLER);
	signal(SIGINT, NULL_HANDLER);
}

void	default_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_sighandler);
}
