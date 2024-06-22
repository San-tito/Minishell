/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:30:57 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 20:25:40 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

typedef struct s_variable
{
	char		*name;
	char		*value;
	int			attributes;
}				t_variable;

typedef struct s_varlist
{
	t_variable	**list;
	int			list_size;
	int			list_len;
}				t_varlist;

# define ATT_EXPORT 0x0000001
# define ATT_READONLY 0x0000002

/* ************************************************************************** */
/*                            shell variables                                 */
/* ************************************************************************** */
int				update_env(char *env_prefix, char *value);
int				delete_env(const char *name);
char			*find_env(const char *name);
int				add_exported(char *str, int append);
void			bind_variable(char *name, char *value, int attributes);
void			initialize_shell_variables(char **env);
void			initialize_shell_level(void);
void			set_pwd(void);
void			clear_variable(t_variable *var);

t_varlist		*vlist_alloc(int nentries);
t_varlist		*varlist(void);
void			vlist_add(t_varlist *vlist, t_variable *var);
void			vlist_clear(void);

#endif
