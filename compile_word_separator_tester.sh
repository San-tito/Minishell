make -C ft_libft
cc src/parser/separate_words.c src/parser/separate_words_utils.c src/parser/lexer_utils.c src/parser/tokenizer.c src/parser/tokenizer_utils.c src/parser/handle_tokens.c lexer_testers/test_words.c ft_libft/libft.a -o word_separator_tester -I ./include/
