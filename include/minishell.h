/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/06/14 00:21:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "command.h"
# include "error.h"
# include "ft_printf.h"
# include "general.h"
# include "history.h"
# include "make_cmd.h"
# include "readline.h"
# include "rlprivate.h"
# include "sh_malloc.h"
# include "variables.h"

# define PROGRAM "minishell"

# define NO_PIPE -1

# define EXECUTION_FAILURE 1
# define EXECUTION_SUCCESS 0

# define EX_BADUSAGE 2
# define EX_NOEXEC 126
# define EX_NOTFOUND 127

# define HEREDOC_MAX 16

# define AND_AND 3
# define OR_OR 5

#endif
