
#include "execute_cmd.h"
#include "minishell.h"
#include "sig.h"
#include "lexer_utils.h"
#include "parser_utils.h"

static void print_words(t_list *lst)
{
	if (lst == NULL)
		ft_printf("Word list is NULL.");
	else
		ft_printf("Separated words: ");
	while (lst != NULL)
	{
		ft_printf("[%s] ", (char *)lst->content);
		lst = lst->next;
	}
	ft_printf("\n");
}

static void	test_separate_words(char *job)
{
	t_list  *words;

	ft_printf("Words to separate: [%s]\n", job);
	words = separate_words(job);
	print_words(words);
	clear_word_list(&words);
}

static void	test_empty_words(char *job)
{
	t_list  *words;

	ft_printf("Words to separate: [%s]\n", job);
	words = separate_words(job);
	remove_empty_words(&words);
	print_words(words);
	clear_word_list(&words);
}

static void	print_token(t_token *token)
{
	ft_printf("[%d, %s] ", token->type, token->content);
}

static void	print_tokens(t_list *tokens)
{
	if (tokens == NULL)
		ft_printf("Token list is NULL.");
	else
		ft_printf("Tokens created [TOKEN-TYPE/TOKEN-DATA]:\n");
	while (tokens != NULL)
	{
		print_token((t_token*)tokens->content);
		tokens = tokens->next;
	}
	ft_printf("\n");
}

static void	test_tokenize_words(char *job)
{
	t_list  *words;
	t_list	*tokens;

	ft_printf("Words to separate: [%s]\n", job);
	words = separate_words(job);
	remove_empty_words(&words);
	print_words(words);
	tokens = tokenizer(&words);
	print_tokens(tokens);
	clear_word_list(&words);
	clear_tokens(&tokens);
}

static void	test_expansor(char *job)
{
	t_list  *words;
	t_list	*tokens;

	ft_printf("Words to separate: [%s]\n", job);
	words = separate_words(job);
	remove_empty_words(&words);
	print_words(words);
	tokens = tokenizer(&words);
	expansor(&tokens);
	print_tokens(tokens);
	clear_word_list(&words);
	clear_tokens(&tokens);
}

static void test_remove_quotes(char *job)
{
	t_list  *words;
	t_list	*tokens;

	ft_printf("Words to separate: [%s]\n", job);
	words = separate_words(job);
	remove_empty_words(&words);
	print_words(words);
	tokens = tokenizer(&words);
	expansor(&tokens);
	print_tokens(tokens);
	clear_word_list(&words);
	remove_quotes(&tokens);
	print_tokens(tokens);
	clear_tokens(&tokens);
}

static void	test_checker(char *job)
{
	t_list	*tokens;

	ft_printf("Job: [%s]\n\t", job);
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
		ft_printf("\n");
		//clear_command(command);
	}
}

static void	test_all_separate_words()
{
	ft_printf("{SEPARATE WORDS}-Correct Tests:\n");
	test_separate_words("test1 test2");
	test_separate_words("test1 test2 test3");
	test_separate_words("test1");
	test_separate_words("test1 \"test2\"\" test3\" test4");
	test_separate_words("test1 \"\'\" test2");
	test_separate_words("test1 \'\"\' test2");
	test_separate_words("test1           test2");
	test_separate_words("test1 test2    ");
	test_separate_words("    test1 test2");
	test_separate_words("                                                      ");
	test_separate_words("");
	test_separate_words("expand $HOME b");
	test_separate_words("expand \'$HOME\' b");
	test_separate_words("expand \"$HOME\" b");
	test_separate_words("expand \"\'$HOME\'\" b");
	test_separate_words("expand \'\"$HOME\"\' b");
	test_separate_words("test1 $SHLVL test2");
	test_separate_words("test1 $$ test2");
	test_separate_words("test1 $? test2");
	test_separate_words("test1 $ test2 $a");
	test_separate_words("$a");
	test_separate_words("$");
	ft_printf("\n{SEPARATE WORDS}-Incorrect Tests:\n");
	test_separate_words("test1 \" test2");
	test_separate_words("test3 \' test4");
	test_separate_words("test3 \'\" test4");
	test_separate_words("test3 \"\' test4");
}

static void	test_all_remove_empty_words()
{
	ft_printf("\n{REMOVE EMPTY WORDS}:\n");
	test_empty_words("test1 test2");
	test_empty_words("test1 test2 test3");
	test_empty_words("test1");
	test_empty_words("test1 \"test2\"\" test3\" test4");
	test_empty_words("test1 \"\'\" test2");
	test_empty_words("test1 \'\"\' test2");
	test_empty_words("test1           test2");
	test_empty_words("test1 test2    ");
	test_empty_words("    test1 test2");
	test_empty_words("                                                      ");
	test_empty_words("");
	test_empty_words("expand $HOME b");
	test_empty_words("expand \'$HOME\' b");
	test_empty_words("expand \"$HOME\" b");
	test_empty_words("expand \"\'$HOME\'\" b");
	test_empty_words("expand \'\"$HOME\"\' b");
	test_empty_words("test1 $SHLVL test2");
	test_empty_words("test1 $$ test2");
	test_empty_words("test1 $? test2");
	test_empty_words("test1 $ test2 $a");
	test_empty_words("$a");
	test_empty_words("$");
}

static void	test_all_tokenizer()
{
	ft_printf("\n{TOKENIZER}-Correct Tests:\n");
	test_tokenize_words("test1 | test2");
	test_tokenize_words("test1|test2");
	test_tokenize_words("test1 && test2");
	test_tokenize_words("test1&&test2");
	test_tokenize_words("test1 || test2");
	test_tokenize_words("test1||test2");
	test_tokenize_words("test1 | test2 && test3 || test4");
	test_tokenize_words("test1 | test2 && test3 || test4 && test4 | test5");
	test_tokenize_words("test1 >a");
	test_tokenize_words("test1 > a");
	test_tokenize_words("test1 >a>b>c");
	test_tokenize_words("test1 >a>b >c");
	test_tokenize_words("test1 >>a<<b<c>d");
	test_tokenize_words("test1 >>a<<b<c>d | test2");
	test_tokenize_words(" <a test1 >b < c | test2 >a && >>b test3 < c > d || test4");
	test_tokenize_words("(test1)");
	test_tokenize_words("(test1 < a)");
	test_tokenize_words("(test1 < a | test2 > b)");
	test_tokenize_words(" ( test1 < a | test2 > b )&& test3");
	test_tokenize_words("(test1 < a | (test2 > b)) && test3");
	test_tokenize_words("(test1 < a | (test2 > b || (test3 || (test5) && test6))) && test4");
	test_tokenize_words("(test1 < a | (test2 > b || (>a test3 || (test5 <a) && test6))) && test4");
	ft_printf("\n{TOKENIZER}-Incorrect Tests:\n");
	test_tokenize_words("&");
	test_tokenize_words("test1 ||& test2");
	test_tokenize_words("test1 &|| test2");
	test_tokenize_words("test1 <& test2");
	test_tokenize_words("((&)|(&))");
}

static void	test_all_expansor()
{
	ft_printf("\n{EXPANSOR}:\n");
	test_expansor("$HOME");
	test_expansor("\'$HOME\'");
	test_expansor("\"$HOME\"");
	test_expansor("\"\'$HOME\'\"");
	test_expansor("\'\"$HOME\"\'");
	test_expansor("test1$HOME");
	test_expansor("\"test1$HOME\"");
	test_expansor("test1 \"test2$HOME\"\" test3\" test4");
	test_expansor("test1 $SHLVL test2");
	test_expansor("test1 $$ test2");
	test_expansor("test1 $? test2");
	test_expansor("$a");
	test_expansor("$?");
	test_expansor("$$");
	test_expansor("$");
	test_expansor("test1 $ test2 $a");
}

static void	test_all_remove_quotes()
{
	ft_printf("\n{REMOVE QUOTES}:\n");
	test_remove_quotes("test1 \"test2\"\" test3\" test4");
	test_remove_quotes("test1 \"test2$HOME\"\" test3\" test4");
	test_remove_quotes("test1 \"test2\'$HOME\' test3\" test4");
	test_remove_quotes("test1 \"test2\'\'\'\"\'\"\'\" \'\'test3\" test4");
}

static void	test_all_check_tokens()
{
	ft_printf("\n{CHECK TOKENS}-Incorrect Tests:\n");
	test_tokenize_words("test1|");
	test_tokenize_words("test1||");
	test_tokenize_words("test1&&");
	test_tokenize_words("|");
	test_tokenize_words("||");
	test_tokenize_words("(");
	test_tokenize_words(")");
	test_tokenize_words("|test1");
	test_tokenize_words("||test1");
	test_tokenize_words("&&test1");
	test_tokenize_words("test1 ||| test2");
	test_tokenize_words("test1 || | test2");
	test_tokenize_words("test1 | || test2");
	test_tokenize_words("test1 || || test2");
	test_tokenize_words("test1 >< test2");
	test_tokenize_words("test1 <> test2");
	test_tokenize_words("test1 <<>> test2");
	test_tokenize_words("test1 >><< test2");
	test_tokenize_words("test1 >>> test2");
	test_tokenize_words("test1)test2(test3 test4");
	test_tokenize_words(" (test1)test2(test3) test4");
	test_tokenize_words(" (test1)test2)test3( test4");
	test_tokenize_words("(test1)test2) ");
	test_tokenize_words("((test1)test2");
	test_tokenize_words("((test1) (test2))");
	test_tokenize_words("(())");
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
	test_checker("echo a | (echo b) | echo c");
}

static void	test_parser()
{
	ft_printf("\nCommand parser checker:\n");
	test_parse_command("echo a | echo b");
	test_parse_command("echo a | echo b && >a echo c <c");
	test_parse_command("echo a | (echo b) | echo c");
	test_parse_command("echo a | (echo b| (echo c)) | echo c");
}


int main(void)
{
	//test_all_separate_words();
	//test_all_remove_empty_words();
	//test_all_tokenizer();
	//test_all_expansor();
	test_all_remove_quotes();
	//test_all_check_tokens();
	//test_lexer();
	//test_parser();
	return (0);
}