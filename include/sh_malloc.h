/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:43:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 13:23:59 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_MALLOC_H
# define SH_MALLOC_H

# include <stddef.h>
# include "ft_printf.h"
# include <dirent.h>

/* ************************************************************************** */
/*                defines for the `sh' memory allocation functions            */
/* ************************************************************************** */
void	*sh_malloc(size_t bytes);
void	*sh_realloc(void *ptr, size_t size);
void	sh_free(void *string);
void	sh_doublefree(void **array);
char	*sh_strdup(const char *str);
char	*sh_substr(const char *str, unsigned int start, size_t len);
char	*sh_strjoin(char const *s1, char const *s2);
t_list	*sh_lstnew(void *content);
char	*sh_itoa(int n);
DIR		*sh_opendir(const char *str);
char	**sh_split(char *str, char value);

#endif
