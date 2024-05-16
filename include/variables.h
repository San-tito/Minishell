/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:30:57 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/16 13:45:12 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

/* ************************************************************************** */
/*                            shell variables                                 */
/* ************************************************************************** */
void		update_env(const char *env_prefix, const char *value);
int			unset_var(const char *name);
char		**add_or_replace_exported_var(char *assign);
void		initialize_shell_variables(char **env);
void		initialize_shell_level(void);
void		set_pwd(void);

extern char	**environ;

#endif
