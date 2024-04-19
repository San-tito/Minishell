/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:55:19 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 16:45:19 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "command.h"
# include "ft_printf.h"

/* ************************************************************************** */
/*             The thing that we build the array of builtins                  */
/* ************************************************************************** */
typedef int			t_builtin_func(t_word_list *);

typedef struct s_builtin
{
	char			*name;
	t_builtin_func	*function;
}					t_builtin;

/* ************************************************************************** */
/*                       The list of minishell builtins                       */
/* ************************************************************************** */
int					cd_builtin(t_word_list *list);
int					pwd_builtin(t_word_list *list);
int					echo_builtin(t_word_list *list);
int					export_builtin(t_word_list *list);
int					env_builtin(t_word_list *list);
int					unset_builtin(t_word_list *list);
int					exit_builtin(t_word_list *list);

#endif
