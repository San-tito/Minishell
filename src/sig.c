/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:56:46 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/10 14:03:44 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include <stdio.h>

void
sigint_sighandler (int sig)
{
    (void)sig;
}


void	initialize_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
