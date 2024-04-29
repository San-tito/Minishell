/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:30:57 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/29 11:28:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

/* ************************************************************************** */
/*                            shell variables                                 */
/* ************************************************************************** */
void		update_env(const char *env_prefix, const char *value);
char		**unset_var(const char *name);
char		**add_or_replace_exported_var(char *assign);
void		initialize_shell_level(void);

extern char	**environ;

#endif
