/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:26:57 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/10 13:02:24 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* ************************************************************************** */
/*                 declarations of functions appearing in error.c             */
/* ************************************************************************** */
void	internal_error(const char *format, ...);
void	internal_warning(const char *format, ...);
void	sys_error(const char *format, ...);
void	fatal_error(const char *format, ...);

#endif
