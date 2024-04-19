/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:23:20 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 16:55:17 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAR_CMD_H
# define CLEAR_CMD_H

# include "command.h"

/* ************************************************************************** */
/*                       Functions appearing in clear_cmd.c                   */
/* ************************************************************************** */
void	clear_command(t_command *command);
void	clear_words(t_word_list *list);
void	clear_redirects(t_redirect *list);

#endif
