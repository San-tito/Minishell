
#include "../../include/minishell.h"

static void	test_lexer(int fd, char *job)
{
	if (lexer(job))
		dprintf(fd, "Correct.\n");
	else
		dprintf(fd, "Incorrect.\n");
}

/*
 *	Input must be: ./lexer_tester "outfile"
 */
int	main(int argc, char **argv)
{
	int fd;

	if (argc != 2 && argv[1][0] == '\0')
		return (1);
	fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT);
	if (fd == -1)
		return (2);
	test_lexer(fd, "echo \"Hello, world!");		//syntax error: unexpected end of file
	test_lexer(fd, "echo \"Hello, world\")");	//syntax error near unexpected token ')'
	test_lexer(fd, "ls >");						//syntax error near unexpected token 'newline'
	test_lexer(fd, "ls -l &&& pwd");			//syntax error near unexpected token '&'
	test_lexer(fd, "ls -l | |");				//syntax error near unexpected token '|'
	test_lexer(fd, "|");						//syntax error near unexpected token '|'
	test_lexer(fd, "echo \"Hello\" >");			//syntax error near unexpected token 'newline'
	test_lexer(fd, "echo Hello (world)");		//syntax error near unexpected token '('
	test_lexer(fd, "()");						//syntax error near unexpected token ')'
	test_lexer(fd, "ls -l && && pwd");					
	//test_lexer(fd, "$123var = \"value\"");	//Invalid variable name starting with a digit
	test_lexer(fd, "echo \'Hello, world!\"");	//Mismatched use of single and double quotes.
	test_lexer(fd, "echo > \"Hello\" >$file");	//ambiguous redirect
	close(fd);
	return (0);
}
