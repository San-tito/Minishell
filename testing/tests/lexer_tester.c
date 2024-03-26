
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
	//Valid tests.
	test_lexer(fd, "echo");
	test_lexer(fd, "\"\"");
	test_lexer(fd, "\"\'\'\"");
	test_lexer(fd, "echo \"test1\"\'\"\'");
	test_lexer(fd, "echo world \"\"");
	test_lexer(fd, "echo \"(world)()()(((()))))))))))\"");
	test_lexer(fd, "echo \"asc 1 123  	 123		2313	 \' aa   ((((	\n		\"");
	test_lexer(fd, "echo a | cat | cat | cat | cat | cat");
	test_lexer(fd, "echo a >a >b >c >d >e >f >g");
	test_lexer(fd, "");
	test_lexer(fd, "213123 1231231 111 3332  123123");
	test_lexer(fd, "echo > \"Hello, world!\"");
	test_lexer(fd, "		   	 	 	 	   	\t \n \t \n							");
	test_lexer(fd, "cat");

	//Non valid tests.
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
