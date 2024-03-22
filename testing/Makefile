#------------------------------------------------------------------------------
#
#	$ Makefile $
#
#	Makefile to create all tests of the minishell.
#	Creates tests to test the lexer, parser and executor.
#
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#	NAME OF EXECUTABLES
#------------------------------------------------------------------------------
LEXER_TESTER	=	lexer_tester
PARSER_TESTER	=	parser_tester
EXECUTOR_TESTER	=	executor_tester
NAME	=	${LEXER_TESTER} ${PARSER_TESTER} ${EXECUTOR_TESTER}

#------------------------------------------------------------------------------
#	MAIN DIRECTORIES
#------------------------------------------------------------------------------
TESTS		=	tests
INCLUDE		=	../include
OBJ_DIR		=	objects

#------------------------------------------------------------------------------
#	STATIC LIBRARIES
#------------------------------------------------------------------------------
LIBFT_DIR		=	../ft_libft
LIBFT			=	${LIBFT_DIR}/libft.a

#------------------------------------------------------------------------------
#	COMPILATION FLAGS
#------------------------------------------------------------------------------
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
HEADERS			=	-I./${INCLUDE}
OPTIMIZATION	=	-O3
DEBUG			=	-g
SANITIZER		=	-fsanitize=address

#------------------------------------------------------------------------------
#	LINKING LIBRARIES
#------------------------------------------------------------------------------
LIBFT_LINK		=	-L./${LIBFT_DIR} -lft

#------------------------------------------------------------------------------
#	FILES
#------------------------------------------------------------------------------
TESTER_HEADER	=	${INCLUDE}/minishell.h

LEXER_FILES		=	lexer.c
PARSER_FILES	=	parser.c
EXECUTOR_FILES	=	executor.c

LEXER_TESTER_FILES		=	lexer_tester.c
PARSER_TESTER_FILES		=	parser_tester.c
EXECUTOR_TESTER_FILES	=	executor_tester.c


#FILES	=	${LEXER_FILES} ${PARSER_FILES} ${EXECUTOR_FILES} \
#			${LEXER_TESTER_FILES} ${PARSER_TESTER_FILES} ${EXECUTOR_TESTER_FILES}



#------------------------------------------------------------------------------
#	RULE TO GET THE .O COMPILED
#------------------------------------------------------------------------------


#------------------------------------------------------------------------------
#	MAIN RULES TO COMPILE AND CREATE THE EXECUTABLE AND TO CLEAN IT
#------------------------------------------------------------------------------


#------------------------------------------------------------------------------
#	RULES TO CREATE THE TMP DIRECTORIES
#------------------------------------------------------------------------------
${OBJ_DIR}:
	@echo "Creating objects file directory."
	@mkdir -p $@

#------------------------------------------------------------------------------
#	PHONY
#------------------------------------------------------------------------------
.PHONY: all clean fclean re make_libs
