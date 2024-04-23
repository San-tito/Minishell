/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:17:53 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/23 14:54:56 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H

# include <sys/wait.h>
# include <unistd.h>

# define NO_PID -1

typedef struct s_process
{
	struct s_process	*next;
	pid_t				pid;
	int					status;
	int					running;
}						t_process;

/* ************************************************************************** */
/*               structures and definitions used by the jobs.c file           */
/* ************************************************************************** */
pid_t					make_child(void);
int						waitchld(pid_t pid);

#endif
