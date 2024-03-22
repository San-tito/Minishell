
#include "../../include/minishell.h"

/*
 *	Input must be: ./lexer_tester "str_to_test" "outfile"
 */
int	main(int argc, char **argv)
{
	int fd;

	if (argc != 3 && argv[2][0] != '\0')
		return (1);
	fd = open(argv[2], O_WRONLY | O_APPEND | O_CREAT);
	if (fd == -1)
		return (2);
	if (lexer(argv[2]))
		dprintf(fd, "Correct.\n");
	else
		dprintf(fd, "Incorrect.\n");
	close(fd);
	return (0);
}
