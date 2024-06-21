/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:30:57 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/21 20:03:28 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

/* ************************************************************************** */
/*                            shell variables                                 */
/* ************************************************************************** */
int			update_env(const char *env_prefix, const char *value);
int			delete_env(const char *name);
char		*find_env(const char *name, int len, int *offset);
int			add_exported(char *name, int append);
void		initialize_shell_level(void);
void		set_pwd(void);

extern char	**environ;

#endif
