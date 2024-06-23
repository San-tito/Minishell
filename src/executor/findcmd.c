/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:32:10 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/23 02:30:52 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	file_status(const char *name)
{
	struct stat	finfo;
	int			r;

	if (stat(name, &finfo) < 0)
		return (0);
	if (S_ISDIR(finfo.st_mode))
		return (FS_EXISTS | FS_DIRECTORY);
	r = FS_EXISTS;
	if (access(name, X_OK) == 0)
		r |= FS_EXECABLE;
	if (access(name, R_OK) == 0)
		r |= FS_READABLE;
	return (r);
}

static int	absolute_program(const char *string)
{
	return (ft_strchr(string, '/') != NULL);
}

static char	*find_in_path_element(const char *name, char *path)
{
	int		status;
	char	*full_path;
	size_t	path_len;
	size_t	name_len;

	path_len = ft_strlen(path);
	name_len = ft_strlen(name);
	full_path = sh_malloc((path_len + name_len + 2) * sizeof(char));
	ft_strlcpy(full_path, path, path_len + 1);
	if (*(full_path + path_len - 1) != '/')
		ft_strlcat(full_path, "/", path_len + 2);
	ft_strlcat(full_path, name, path_len + name_len + 2);
	status = file_status(full_path);
	if ((status & FS_EXECABLE))
		return (full_path);
	sh_free(full_path);
	return (NULL);
}

char	*search_for_command(const char *pathname)
{
	char	*command;
	char	*path_list;
	char	**paths;
	int		path_index;

	path_index = 0;
	path_list = find_env("PATH");
	if (!pathname)
		return (NULL);
	else if (absolute_program(pathname))
		return (sh_strdup(pathname));
	else if (!path_list || !*path_list)
		return (NULL);
	paths = ft_split(path_list, ':');
	if (!paths)
		return (NULL);
	while (*(paths + path_index))
	{
		command = find_in_path_element(pathname, *(paths + path_index));
		if (command)
			break ;
		path_index++;
	}
	return (sh_doublefree((void **)paths), command);
}
