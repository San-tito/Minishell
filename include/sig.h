/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:01:41 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 21:32:18 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>

# define NULL_HANDLER SIG_DFL

/* ************************************************************************** */
/*                          signal handler definitions                        */
/* ************************************************************************** */
void	initialize_signals(void);
void	reset_terminating_signals(void);

#endif
