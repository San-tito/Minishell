# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 15:31:23 by sguzman           #+#    #+#              #
#    Updated: 2024/01/20 12:31:44 by sguzman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #    

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME		= minishell
CC 		= cc
CFLAGS	= -Wall -Wextra -Werror
DFLAGS	= -MMD -MF $(@:.o=.d)

################################################################################
#                                 INSTALL CONFIG                              #
################################################################################

bindir = /usr/local/bin
man1dir = /usr/local/man/man1
infodir = /usr/local/info

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_PATH	= ./src

OBJS_PATH 	= ./build

INCLUDE_PATH	= ./include

DOCS_PATH	= ./docs

HEADER	= $(INCLUDE_PATH)/minishell.h

SRCS =	

MAIN 		= minishell.c 

################################################################################
#                                  Makefile  objs                              #
################################################################################

OBJS		= $(addprefix objs/, ${SRCS:.c=.o})

OBJS_MAIN	= $(addprefix $(OBJS_PATH)/, ${MAIN:.c=.o})

DEPS		= $(addprefix objs/, ${SRCS:.c=.d})

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

-include $(DEPS) $(DEPS_MAIN)
$(NAME):	$(OBJS) $(OBJS_MAIN)
			@$(CC) $(CFLAGS) $(DFLAGS) -I $(INCLUDE_PATH) -o $@ $^
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Building program:" "$(CYAN)" $@ "$(GREEN)" "[✓]" "$(RESET)"

$(OBJS_PATH)/%.o: 	$(SRCS_PATH)/%.c $(HEADER) Makefile
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(INCLUDE_PATH)
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Compiling:" "$(CYAN)" $< "$(GREEN)" "[✓]" "$(RESET)"

installdirs:
			@mkdir -p $(bindir)
			@mkdir -p $(man1dir)
			@mkdir -p $(infodir)

install:	all installdirs	
			@install -m 0755 $(NAME) $(bindir)/$(NAME)
			@$(MAKE) man1dir=$(man1dir) infodir=$(infodir) $@ -C $(DOCS_PATH) --no-print-directory
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Installing program:" "$(CYAN)" $(bindir)/$(NAME) "$(GREEN)" "[✓]" "$(RESET)"

uninstall:	banner
			@rm -rf $(bindir)/$(NAME) 
			@$(MAKE) man1dir=$(man1dir) infodir=$(infodir) $@ -C $(DOCS_PATH) --no-print-directory
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Uninstalling program:" "$(CYAN)" $(bindir)/$(NAME) "$(GREEN)" "[✓]" "$(RESET)"

clean:		banner
			@rm -rf $(OBJS_PATH)
			@printf "%b%-42s%-42b%b%s%b\n" "$(BLUE)" "$@:" "$(CYAN)" "$(GREEN)" "[✓]" "$(RESET)"

fclean:		banner clean
			@rm -rf $(NAME)
			@printf "%b%-42s%-42b%b%s%b\n" "$(BLUE)" "$@:" "$(CYAN)" "$(GREEN)" "[✓]" "$(RESET)"

re:			fclean all

.PHONY:		all banner clean fclean re


