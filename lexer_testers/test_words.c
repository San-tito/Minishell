
#include "lexer.h"
#include "separate_words.h"
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
		clear_words(&words);
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
		clear_words(&words);
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
		clear_words(&words);
		clear_tokens(&tokens);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

int main(void)
{
	ft_printf(1, "Correct Tests:\n");
	test_words("test1 test2");
	test_words("test3 \"test4\"\" test5\" test6");
	test_words("test7 \"\'\" test8");
	test_words("test9 \'\"\' test10");
	test_words("test9           test10");
	test_words("test11 test12    ");

	ft_printf(1, "Incorrect Tests:\n");
	//test_words("");??
	test_words("test1 \" test2");
	test_words("test3 \' test4");

	ft_printf(1, "Remove empty words:\n");
	test_empty("test9           test10");
	test_empty("test11 test12    ");
	test_empty("                                                      ");
	//test_empty("");??

	ft_printf(1, "Tokenize:\n");
	test_tokenizer("test1 test2");
	test_tokenizer("test1|||test2");
	test_tokenizer("test1|test2|test3|test4");
	test_tokenizer("test1)test2(test3)test4");
	test_tokenizer(")");
	test_tokenizer("&");
	//test_tokenizer("")??
	return (0);
}
