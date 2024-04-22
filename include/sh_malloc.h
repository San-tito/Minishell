/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:43:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 16:44:28 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_MALLOC_H
# define SH_MALLOC_H

#include <stddef.h>

/* ************************************************************************** */
/*                defines for the `sh' memory allocation functions            */
/* ************************************************************************** */
void	*sh_malloc(size_t bytes);
void	sh_free(void *string);
void	sh_doublefree(void **array);

#endif
