
#include "lexer.h"
#include "separate_words.h"
#include "parser.h"
#include "executor_structs.h"
#include <sys/wait.h>

static void print_words(t_list *lst)
{
	ft_printf(1, "New word list:\n");
	while (lst != NULL)
	{
		ft_printf(1, "Word: [%s]\n", (char *)lst->content);
		lst = lst->next;
	}
}

static void	test_words(char *job)
{
	pid_t	pid;
	int		status;
	t_list  *words;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		words = separate_words(job);
		print_words(words);
		clear_word_list(&words);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

static void	test_empty(char *job)
{
	pid_t	pid;
	int		status;
	t_list  *words;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		words = separate_words(job);
		remove_empty_words(&words);
		print_words(words);
		clear_word_list(&words);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

static void	print_token(t_token *token)
{
	ft_printf(1, "Token type: [%d], Token data: [%s].\n", token->type, token->content);
}

static void	print_tokens(t_list *tokens)
{
	ft_printf(1, "New token list:\n");
	while (tokens != NULL)
	{
		print_token((t_token*)tokens->content);
		tokens = tokens->next;
	}
}

static void	test_tokenizer(char *job)
{
	pid_t	pid;
	int		status;
	t_list  *words;
	t_list	*tokens;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		words = separate_words(job);
		remove_empty_words(&words);
		print_words(words);
		tokens = tokenizer(&words);
		print_tokens(tokens);
		clear_word_list(&words);
		clear_tokens(&tokens);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

static void test_quotes(char *job)
{
	pid_t	pid;
	int		status;
	t_list  *words;
	t_list	*tokens;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		words = separate_words(job);
		remove_empty_words(&words);
		print_words(words);
		tokens = tokenizer(&words);
		clear_word_list(&words);
		remove_quotes(&tokens);
		print_tokens(tokens);
		clear_tokens(&tokens);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

static void	test_checker(char *job)
{
	pid_t	pid;
	int		status;
	t_list  *words;
	t_list	*tokens;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		words = separate_words(job);
		remove_empty_words(&words);
		tokens = tokenizer(&words);
		clear_word_list(&words);
		remove_quotes(&tokens);
		check_tokens(&tokens);
		print_tokens(tokens);
		clear_tokens(&tokens);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

static void	print_simple_command(t_simple_com *command)
{
	ft_printf(1, "Node is simple command.\n");
	//print words
	//print redirects
}

static void	print_command(t_command *command);

static void	print_connection(t_connection *connection)
{
	ft_printf(1, "Node is connection. Connection is: [%d].\n", connection->connector);
	print_command(connection->first);
	print_command(connection->second);
}

static void	print_command(t_command *command)
{
	t_command_type	type;

	type = command->type;
	if (type == cm_simple)
		print_simple_command((t_simple_com *)(command->value));
	else if (type == cm_connection)
		print_connection((t_connection *)(command->value));
	else
        ft_printf(1, "clear_subshell.\n");
		//clear_subshell((t_simple_com *)((*command)->value));
}

static void	test_parser(char *job)
{
	pid_t	pid;
	int		status;
	t_command	*command;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		ft_printf(1, "New test.\n");
		command = parser(job);
		print_command(command);
		clear_command(&command);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

int main(void)
{
	/*
	ft_printf(1, "Correct Tests:\n");
	test_words("test1 test2");
	test_words("test3 \"test4\"\" test5\" test6");
	test_words("test7 \"\'\" test8");
	test_words("test9 \'\"\' test10");
	test_words("test9           test10");
	test_words("test11 test12    ");

	ft_printf(1, "\nIncorrect Tests:\n");
	//test_words("");??
	test_words("test1 \" test2");
	test_words("test3 \' test4");

	ft_printf(1, "\nRemove empty words:\n");
	test_empty("test9           test10");
	test_empty("test11 test12    ");
	test_empty("                                                      ");
	//test_empty("");??

	ft_printf(1, "\nTokenize:\n");
	test_tokenizer("test1 test2");
	test_tokenizer("test1|||test2");
	test_tokenizer("test1|test2|test3|test4");
	test_tokenizer("test1)test2(test3)test4");
	test_tokenizer(")");
	test_tokenizer("&");
	//test_tokenizer("")??

	ft_printf(1, "\nRemove quotes:\n");
	test_quotes("test1 \"test4\"\" test5\" test2");
	test_quotes("test1 \"test4\'\' test5\" test2");
	test_quotes("test1 \"test4\'\'\'\"\'\"\'\" \'\'test5\" test2");

	ft_printf(1, "\nToken checker:\n");
	test_checker("test1 () test2");
	test_checker("test1 | test2 |");
	test_checker("|");
	test_checker("(");
	test_checker(")");
	test_checker("a");
	test_checker("test1 ( test2");
	test_checker("test1 && | test2");
	test_checker("test1 ||| test2");
	test_checker("test1 <> test2");
	test_checker("test1 > test2 >");
	test_checker("test1 > test2 > test3");
	test_checker("test1 > test2 (test4) | test5");
	test_checker("te<st1");
	test_checker("test1 | test2 || test3 && test0 test4 > test5 < test6 ( test7 ) >> test8 << test9");
	test_checker("<< test0");
	test_checker("test1 <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a");
	test_checker("echo a ( echo c )");
	test_checker("echo a > > echo b"); //??
	test_checker("echo a > < echo b"); //??
 */
	ft_printf(1, "\nCommand parser checker:\n");
	test_parser("echo a");
	test_parser("echo a | echo b");
	test_parser("echo a | echo b && >a echo c <c");
	return (0);
}
