make -C ft_libft
cc src/parser/lexer_clear_structs.c src/parser/lexer_remove_quotes.c src/parser/separate_words_utils.c src/parser/separate_words.c src/parser/tokenizer_handle_tokens.c src/parser/tokenizer_utils.c src/parser/tokenizer.c src/parser/lexer_utils.c lexer_testers/test_words.c ft_libft/libft.a -o word_separator_tester -I ./include/
