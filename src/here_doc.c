/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:55:43 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/14 01:08:54 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "input.h"
#include "minishell.h"
#include "sig.h"

static char	*append_to_document(char *document, const char *line)
{
	int		len;
	int		document_size;
	char	*new_document;

	document_size = ft_strlen(document);
	len = ft_strlen(line);
	new_document = sh_malloc(document_size + len + 2);
	ft_memcpy(new_document, document, document_size);
	ft_memcpy(new_document + document_size, line, len);
	new_document[document_size + len] = '\n';
	new_document[document_size + len + 1] = '\0';
	sh_free(document);
	return (new_document);
}

void	make_here_document(t_redirect *temp)
{
	int		redir_len;
	char	*redir_word;
	char	*line;
	char	*document;

	redir_word = temp->filename;
	redir_len = ft_strlen(redir_word);
	document = sh_malloc(1);
	*document = '\0';
	line = readline(get_secondary_prompt());
	while (line)
	{
		if (!ft_strncmp(line, redir_word, redir_len) && line[redir_len] == '\0')
			break ;
		document = append_to_document(document, line);
		line = readline(get_secondary_prompt());
	}
	if (line == 0)
		internal_warning("here-document delimited by end-of-file (wanted `%s')",
			redir_word);
	temp->filename = document;
}
