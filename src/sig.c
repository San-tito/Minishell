/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/14 15:16:13 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "input.h"
#include "minishell.h"
#include "sig.h"

void	sigint_sighandler(int sig)
{
	signal(sig, sigint_sighandler);
	if (g_last_exit_value < 128)
		g_last_exit_value = 128 + SIGINT;
	if (rl_readline_state & RL_STATE_SIGHANDLER)
	{
		// rl_visible_prompt_length = rl_expand_prompt(get_primary_prompt());
		ft_putchar_fd(10, 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	reset_terminating_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	initialize_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_sighandler);
}
