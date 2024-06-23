
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

static void test_expand_wildcards(char *job)
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

static void	test_lexer(char *job)
{
	t_list	*tokens;
	char	err;

	err = 0;
	ft_printf("Job: [%s]\n\t", job);
	tokens = lexer(job, &err);
	if (!err)
	{
		ft_printf("Correct!\n");
		clear_tokens(&tokens);
	}
}

static void	test_parser(char *job)
{
	t_command	*command;

	ft_printf("Job: [%s]\n\t", job);
	command = parse_command(job);
	if (command != NULL)
	{
		print_command(command);
		ft_printf("\n");
		clear_command(command);
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
	test_tokenize_words("                                                      ");
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
	test_expansor("                                                      ");
	test_expansor("test1 $SHLVL test2");
	test_expansor("test1 $$ test2");
	test_expansor("test1 $? test2");
	test_expansor("$a");
	test_expansor("$?");
	test_expansor("$$");
	test_expansor("$");
	test_expansor("test1 $ test2 $a");
	test_expansor("test1 $ test2** $a");
}

static void	test_all_remove_quotes()
{
	ft_printf("\n{REMOVE QUOTES}:\n");
	test_remove_quotes("test1 \"test2\"\" test3\" test4");
	test_remove_quotes("test1 \"test2$HOME\"\" test3\" test4");
	test_remove_quotes("test1 \"test2\'$HOME\' test3\" test4");
	test_remove_quotes("test1 \"test2\'\'\'\"\'\"\'\" \'\'test3\" test4");
}

static void	test_all_wildcards()
{
	ft_printf("\n{EXPAND WILDCARDS}:\n");
	test_expand_wildcards("echo");
	test_expand_wildcards("*");
	test_expand_wildcards("echo *");
	
	test_expand_wildcards("echo \'*\'");
	test_expand_wildcards("echo diablo$HOME");
	
	test_expand_wildcards("echo **");
}

static void	test_all_lexer()
{
	ft_printf("\n{LEXER}-Correct Tests:\n");
	test_lexer("a");
	test_lexer("test1 > test2 > test3");
	test_lexer("te<st1");
	test_lexer("<< test0");
	test_lexer("echo a | (echo b) | echo c");
	ft_printf("\n{LEXER}-Incorrect Tests:\n");
	test_lexer("test1|");
	test_lexer("test1||");
	test_lexer("test1&&");
	test_lexer("|");
	test_lexer("||");
	test_lexer("(");
	test_lexer(")");
	test_lexer("|test1");
	test_lexer("||test1");
	test_lexer("&&test1");
	test_lexer("test1 ||| test2");
	test_lexer("test1 || | test2");
	test_lexer("test1 | || test2");
	test_lexer("test1 || || test2");
	test_lexer("echo a > > echo b");
	test_lexer("test1 >< test2");
	test_lexer("test1 <> test2");
	test_lexer("test1 <<>> test2");
	test_lexer("test1 >><< test2");
	test_lexer("test1 >>> test2");
	test_lexer("test1 <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a");
	test_lexer("test1 > test2 >");
	test_lexer("test1 ( test2");
	test_lexer("test1 () test2");
	test_lexer("test1 | test2 |");
	test_lexer("test1 | test2 || test3 && test0 test4 > test5 < test6 ( test7 ) >> test8 << test9");
	test_lexer("test1 > test2 (test4) | test5");
	test_lexer("test1)test2(test3 test4");
	test_lexer(" (test1)test2(test3) test4");
	test_lexer(" (test1)test2)test3( test4");
	test_lexer("(test1)test2) ");
	test_lexer("((test1)test2");
	test_lexer("((test1) (test2))");
	test_lexer("(())");
}

static void	test_all_parser()
{
	ft_printf("\nCommand parser checker:\n");
	test_parser("echo a | echo b");
	test_parser("echo a | echo b && >a echo c <c");
	test_parser("echo a | (echo b) | echo c");
	test_parser("echo a | (echo b| (echo c)) | echo c");
	test_parser("echo a | ( <a echo b >c <a| (echo c <a >b)) | echo c");
	test_parser("$a");
	test_parser("$a >b b");
	test_parser("$a echo \"test\"");
	test_parser("cat > $a");
}

int main(void)
{
	test_all_separate_words();
	test_all_remove_empty_words();
	test_all_tokenizer();
	test_all_expansor();
	test_all_wildcards();
	test_all_remove_quotes();
	test_all_lexer();
	test_all_parser();
	//test_parser("echo a | echo b");
	vlist_clear(varlist());
	return (0);
}
