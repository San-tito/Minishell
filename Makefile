# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 15:31:23 by sguzman           #+#    #+#              #
#    Updated: 2024/04/29 12:03:18 by sguzman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #    

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME		= minishell
CC 		= cc
CFLAGS	= -Wall -Wextra -Werror
DFLAGS	= -MMD -MF $(@:.o=.d)
RLFLAGS = -lcurses

################################################################################
#                                 INSTALL CONFIG                              #
################################################################################

prefix=/usr/local
bindir = $(prefix)/bin
man1dir = $(prefix)/man/man1

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################
SRCS_PATH	= ./src

OBJS_PATH 	= ./build

INCLUDE_PATH	= ./include

DOCS_PATH	= ./docs

BUILTINS_PATH	= $(SRCS_PATH)/builtins

PARSER_PATH	= $(SRCS_PATH)/parser

EXECUTOR_PATH = $(SRCS_PATH)/executor

LIBFTPRINTF_PATH = ./libs/libftprintf

LIBFTPRINTF		= $(LIBFTPRINTF_PATH)/libftprintf.a

READLINE_PATH = ./libs/readline

READLINE = $(READLINE_PATH)/libhistory.a $(READLINE_PATH)/libreadline.a 

HEADER	= $(INCLUDE_PATH)/minishell.h

SRCS = clear_cmd.c \
       error.c \
       list.c \
       make_cmd.c \
       print_cmd.c \
       read_cmd.c \
       prompt.c \
       sh_malloc.c \
	   sig.c \
       variables.c

PARSERS = lexer_check_tokens_2.c \
          lexer_check_tokens.c \
          lexer_clear.c \
          lexer_remove_quotes.c \
          lexer_separate_words.c \
          lexer_utils.c \
          lexer.c \
          parser_handle_heredocs.c \
          parser_manage_subshell.c \
          parser_simple_command.c \
          parser_utils.c \
          parser.c \
          tokenizer_utils.c \
          tokenizer.c

EXECUTORS = connection.c \
            execute_cmd.c \
            findcmd.c \
            jobs.c \
            pipeline.c \
            redir.c \
            simple.c

BUILTINS = builtins.c \
           cd.c \
           echo.c \
           env.c \
           exit.c \
           export.c \
           pwd.c \
           unset.c

MAIN = minishell.c

################################################################################
#                                  Makefile  objs                              #
################################################################################

OBJS		= $(addprefix $(OBJS_PATH)/, ${SRCS:.c=.o})

OBJS_BUILTIN		= $(addprefix $(OBJS_PATH)/, ${BUILTINS:.c=.o})

OBJS_PARSER	= $(addprefix $(OBJS_PATH)/, ${PARSERS:.c=.o})

OBJS_EXECUTOR = $(addprefix $(OBJS_PATH)/, ${EXECUTORS:.c=.o})

OBJS_MAIN	= $(addprefix $(OBJS_PATH)/, ${MAIN:.c=.o})

DEPS		= $(addprefix $(OBJS_PATH)/, ${SRCS:.c=.d})

DEPS_BUILTIN		= $(addprefix $(OBJS_PATH)/, ${BUILTINS:.c=.d})

DEPS_PARSER	= $(addprefix $(OBJS_PATH)/, ${PARSERS:.c=.d})

DEPS_EXECUTOR = $(addprefix $(OBJS_PATH)/, ${EXECUTORS:.c=.d})

DEPS_MAIN	= $(addprefix $(OBJS_PATH)/, ${MAIN:.c=.d})

################################################################################
#                                 Makefile logic                               #
################################################################################

RED         	= \033[0;31m
GREEN       	= \033[0;32m
YELLOW      	= \033[0;33m
BLUE        	= \033[0;34m
PURPLE      	= \033[0;35m
CYAN        	= \033[0;36m
RESET       	= \033[m

################################################################################
#                                 Makefile rules                               #
################################################################################

all: banner $(NAME) 

banner:
	@printf "%b" "$(PURPLE)"
	@echo
	@echo "# **************************************************************************** #"
	@echo "#                                                                              #"
	@echo "#                                                         :::      ::::::::    #"
	@echo "#    minishell                                          :+:      :+:    :+:    #"
	@echo "#                                                     +:+ +:+         +:+      #"
	@echo "#    By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+         #"
	@echo "#    By: mpovill- <mpovill-@student.42barcel>     +#+#+#+#+#+   +#+            #"
	@echo "#                                                      #+#    #+#              #"
	@echo "#                                                     ###   ########.fr        #"
	@echo "#                                                                              #"
	@echo "# **************************************************************************** #"
	@echo
	@printf "%b" "$(RESET)"

-include $(DEPS) $(DEPS_BUILTIN) $(DEPS_PARSER) $(DEPS_EXECUTOR) $(DEPS_MAIN)
$(NAME):	$(OBJS_BUILTIN) $(OBJS_PARSER) $(OBJS_EXECUTOR) $(OBJS) $(OBJS_MAIN) $(READLINE) $(LIBFTPRINTF)
			@$(CC) $(CFLAGS) $(DFLAGS) -I $(INCLUDE_PATH) $^ $(RLFLAGS) -o $@ 
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Building program:" "$(CYAN)" $@ "$(GREEN)" "[✓]" "$(RESET)"

$(READLINE):
			@make -C $(READLINE_PATH) > /dev/null
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Building Readline library:" "$(CYAN)" $@ "$(GREEN)" "[✓]" "$(RESET)"

$(LIBFTPRINTF):
			@make bonus -C $(LIBFTPRINTF_PATH) > /dev/null
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Building Libftprintf library:" "$(CYAN)" $@ "$(GREEN)" "[✓]" "$(RESET)"

$(OBJS_PATH)/%.o: 	$(SRCS_PATH)/%.c $(HEADER) Makefile
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(INCLUDE_PATH) -I $(LIBFTPRINTF_PATH)/include
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Compiling:" "$(CYAN)" $< "$(GREEN)" "[✓]" "$(RESET)"

$(OBJS_PATH)/%.o: 	$(BUILTINS_PATH)/%.c $(HEADER) Makefile
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(INCLUDE_PATH) -I $(LIBFTPRINTF_PATH)/include
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Compiling:" "$(CYAN)" $< "$(GREEN)" "[✓]" "$(RESET)"

$(OBJS_PATH)/%.o: 	$(PARSER_PATH)/%.c $(HEADER) Makefile
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(INCLUDE_PATH) -I $(LIBFTPRINTF_PATH)/include
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Compiling:" "$(CYAN)" $< "$(GREEN)" "[✓]" "$(RESET)"

$(OBJS_PATH)/%.o: 	$(EXECUTOR_PATH)/%.c $(HEADER) Makefile
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(INCLUDE_PATH) -I $(LIBFTPRINTF_PATH)/include
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Compiling:" "$(CYAN)" $< "$(GREEN)" "[✓]" "$(RESET)"

installdirs:
			@mkdir -p $(bindir)
			@mkdir -p $(man1dir)

install:	all installdirs	
			@install -m 0755 $(NAME) $(bindir)/$(NAME)
			@$(MAKE) man1dir=$(man1dir) $@ -C $(DOCS_PATH) --no-print-directory
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Installing program:" "$(CYAN)" $(bindir)/$(NAME) "$(GREEN)" "[✓]" "$(RESET)"

uninstall:	banner
			@rm -rf $(bindir)/$(NAME) 
			@$(MAKE) man1dir=$(man1dir) infodir=$(infodir) $@ -C $(DOCS_PATH) --no-print-directory
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Uninstalling program:" "$(CYAN)" $(bindir)/$(NAME) "$(GREEN)" "[✓]" "$(RESET)"

clean:		banner
			@make $@ -C $(LIBFTPRINTF_PATH) > /dev/null
			@make $@ -C $(READLINE_PATH) > /dev/null
			@rm -rf $(OBJS_PATH)
			@printf "%b%-42s%-42b%b%s%b\n" "$(BLUE)" "$@:" "$(CYAN)" "$(GREEN)" "[✓]" "$(RESET)"

fclean:		banner clean
			@make $@ -C $(LIBFTPRINTF_PATH) > /dev/null
			@rm -rf $(NAME)
			@printf "%b%-42s%-42b%b%s%b\n" "$(BLUE)" "$@:" "$(CYAN)" "$(GREEN)" "[✓]" "$(RESET)"

re:			fclean all

.PHONY:		all banner clean fclean re $(READLINE) $(LIBFTPRINTF)
