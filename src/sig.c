/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/12 16:50:33 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sig.h"

void	sigint_sighandler(int sig)
{
	(void)sig;
	ft_putchar_fd(10, 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	initialize_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_sighandler);
}
