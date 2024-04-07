
#include "lexer.h"
#include "separate_words.h"
#include <sys/wait.h>

static void print_and_free(t_list **words)
{
	t_list	*lst;

	lst = *words;
	ft_printf(1, "New word list:\n");
	while (lst != NULL)
	{
		ft_printf(1, "Word: [%s]\n", (char *)lst->content);
		lst = lst->next;
	}
	clear_words(words);
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
		print_and_free(&words);
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
		print_and_free(&words);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

int main(void)
{
	t_list  *words;

	ft_printf(1, "Correct Tests:\n");
	test_words("test1 test2");
	test_words("test3 \"test4 test5\" test6");
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
	return (0);
}
