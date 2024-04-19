/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:08:16 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 17:09:59 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

/* Replace the '➜' symbol in the prompt with '❯' */
# define SYMBOL "❯ "
# define CYAN "\001\033[1;36m\002"
# define GREEN "\001\033[1;32m\002"
# define RED "\001\033[1;31m\002"
# define YELLOW "\001\033[1;33m\002"
# define RESET "\001\033[0m\002"

/* ************************************************************************** */
/*                           Functions used for reading input                 */
/* ************************************************************************** */
char			*get_primary_prompt(void);
char			*get_secondary_prompt(void);

#endif
