# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 15:31:23 by sguzman           #+#    #+#              #
#    Updated: 2024/01/20 13:09:55 by sguzman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

MAN            = minishell.1
INFO		= minishell.info
man1dir = 
infodir = 

################################################################################
#                                 Makefile logic                               #
################################################################################

RED             = \033[0;31m
GREEN           = \033[0;32m
YELLOW          = \033[0;33m
BLUE            = \033[0;34m
PURPLE          = \033[0;35m
CYAN            = \033[0;36m
RESET           = \033[m

################################################################################
#                                 Makefile rules                               #
################################################################################

install: installdirs 
	@install -m 644 $(MAN) $(man1dir)/$(MAN)
	@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Installing man page:" "$(CYAN)" $(man1dir)/$(MAN) "$(GREEN)" "[✓]" "$(RESET)"
	@install -m 644 $(INFO) $(infodir)/$(INFO)
	@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Installing info page:" "$(CYAN)" $(infodir)/$(INFO) "$(GREEN)" "[✓]" "$(RESET)"

installdirs:
	@mkdir -p $(man1dir)
	@mkdir -p $(infodir)

uninstall:
	@rm -rf $(man1dir)/$(NAME)
	@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Uninstalling man page:" "$(CYAN)" $(man1dir)/$(NAME) "$(GREEN)" "[✓]" "$(RESET)"
	@rm -rf $(infodir)/$(INFO)
	@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Uninstalling info page:" "$(CYAN)" $(infodir)/$(INFO) "$(GREEN)" "[✓]" "$(RESET)"
	
