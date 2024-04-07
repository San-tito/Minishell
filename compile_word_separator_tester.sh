name_test=word_separator_tester

make -C ft_libft
cc src/parser/separate_words.c src/parser/separate_words_utils.c test_words/main.c ft_libft/libft.a -o ${name_test} -I ./include/
