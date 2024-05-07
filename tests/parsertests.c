
#include "lexer_utils.h"
#include "parser_utils.h"
#include "general.h"

static void print_words(t_list *lst)
{
	ft_printf("New word list:\n");
	while (lst != NULL)
	{
		ft_printf("Word: [%s]\n", (char *)lst->content);
		lst = lst->next;
	}
}

static void	test_words(char *job)
{
	t_list  *words;

	words = separate_words(job);
	print_words(words);
	clear_word_list(&words);
}

static void	test_empty(char *job)
{
	t_list  *words;

	words = separate_words(job);
	remove_empty_words(&words);
	print_words(words);
	clear_word_list(&words);
}

static void	print_token(t_token *token)
{
	ft_printf("Token type: [%d], Token data: [%s].\n", token->type, token->content);
}

static void	print_tokens(t_list *tokens)
{
	ft_printf("New token list:\n");
	while (tokens != NULL)
	{
		print_token((t_token*)tokens->content);
		tokens = tokens->next;
	}
}

static void	test_token(char *job)
{
	t_list  *words;
	t_list	*tokens;

	words = separate_words(job);
	remove_empty_words(&words);
	print_words(words);
	tokens = tokenizer(&words);
	print_tokens(tokens);
	clear_word_list(&words);
	clear_tokens(&tokens);
}

static void test_quotes(char *job)
{
	t_list  *words;
	t_list	*tokens;

	words = separate_words(job);
	remove_empty_words(&words);
	print_words(words);
	tokens = tokenizer(&words);
	clear_word_list(&words);
	remove_quotes(&tokens);
	print_tokens(tokens);
	clear_tokens(&tokens);
}

static void	test_checker(char *job)
{
	t_list	*tokens;

	tokens = lexer(job);
	if (tokens != NULL)
	{
		ft_printf("Correct!\n");
		clear_tokens(&tokens);
	}
}

static void	print_command2(t_command *command);

static void	print_connection(t_connection *connection)
{
	ft_printf("Node is connection. Connection is: [%d].\n", connection->connector);
	print_command2(connection->first);
	print_command2(connection->second);
}

static void	print_subshell(t_command *subshell)
{
	t_command	*command;

	ft_printf("Subshell.\n");
	command = (t_command*)(subshell->value);
	print_command2(command);
}

static void	print_command2(t_command *command)
{
	t_command_type	type;

	type = command->type;
	if (type == cm_simple)
		print_simple_command((t_simple_com *)(command->value));
	else if (type == cm_connection)
		print_connection((t_connection *)(command->value));
	else
		print_subshell((command->value));
}

static void	test_parse_command(char *job)
{
	t_command	*command;

	ft_printf("New test.\n");
	command = parse_command(job);
	if (command != NULL)
	{
		print_command(command);
		printf("\n");
		//clear_command(command);
	}
}

static void	test_separate_words()
{
	ft_printf("Correct Tests:\n");
	test_words("test1 test2");
	test_words("test3 \"test4\"\" test5\" test6");
	test_words("test7 \"\'\" test8");
	test_words("test9 \'\"\' test10");
	test_words("test9           test10");
	test_words("test11 test12    ");

	ft_printf("\nIncorrect Tests:\n");
	//test_words("");??
	test_words("test1 \" test2");
	test_words("test3 \' test4");
}

static void	test_remove_empty_words()
{
	ft_printf("\nRemove empty words:\n");
	test_empty("test9           test10");
	test_empty("test11 test12    ");
	test_empty("                                                      ");
	//test_empty("");??
}

static void	test_tokenizer()
{
	ft_printf("\nTokenize:\n");
	test_token("test1 test2");
	test_token("test1|||test2");
	test_token("test1|test2|test3|test4");
	test_token("test1)test2(test3)test4");
	test_token(")");
	test_token("&");
	//test_token("")??
}

static void	test_q()
{
	ft_printf("\nRemove quotes:\n");
	test_quotes("test1 \"test4\"\" test5\" test2");
	test_quotes("test1 \"test4\'\' test5\" test2");
	test_quotes("test1 \"test4\'\'\'\"\'\"\'\" \'\'test5\" test2");
}

static void	test_lexer()
{
	ft_printf("\nLexer:\n");
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
}

static void	test_parser()
{
	ft_printf("\nCommand parser checker:\n");
	test_parse_command("echo a | echo b");
	test_parse_command("echo a | echo b && >a echo c <c");
}

int main(void)
{
	test_separate_words();
	test_remove_empty_words();
	test_tokenizer();
	test_q();
	test_lexer();
	test_parser();
	return (0);
}