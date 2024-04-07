name_test=word_separator_tester

make -C ft_libft
cc src/parser/separate_words.c src/parser/separate_words_utils.c src/parser/lexer_utils.c lexer_testers/test_words.c ft_libft/libft.a -o ${name_test} -I ./include/
