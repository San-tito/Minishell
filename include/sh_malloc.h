/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:43:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/21 14:19:01 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_MALLOC_H
# define SH_MALLOC_H

# include <stddef.h>

/* ************************************************************************** */
/*                defines for the `sh' memory allocation functions            */
/* ************************************************************************** */
void	*sh_malloc(size_t bytes);
void	*sh_realloc(void *ptr, size_t size);
void	sh_free(void *string);
void	sh_doublefree(void **array);
char	*sh_strdup(char *str);

#endif
