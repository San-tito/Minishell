
#include "../../include/minishell.h"
#include <stdio.h>

/*
 *	Input must be: ./executor_tester "str_to_test" "outfile"
 */
int	main(int argc, char **argv)
{
	int fd;

	if (argc != 3 && argv[2][0] != '\0')
		return (1);
	fd = open(argv[2], O_WRONLY | O_CREAT);
	if (fd == -1)
		return (2);
	//if (lexer(argv[2]))
	//	fprintf(fd, "Correct\n.");
	//else
	//	fprintf(fd, "Incorrect\n.");
	close(fd);
	return (0);
}
