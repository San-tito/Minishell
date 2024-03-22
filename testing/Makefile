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
EXPANSOR_TESTER	=	expansor_tester
PARSER_TESTER	=	parser_tester
EXECUTOR_TESTER	=	executor_tester

NAME	=	${LEXER_TESTER} ${PARSER_TESTER} ${EXECUTOR_TESTER} ${EXPANSOR_TESTER}

#------------------------------------------------------------------------------
#	MAIN DIRECTORIES
#------------------------------------------------------------------------------
TESTS		=	./tests
INCLUDE		=	../include
SRC			=	../src
OBJ_DIR		=	./objects

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

LEXER_FILES		=	${SRC}/lexer.c
LEXER_FILES		+=	${TESTS}/lexer_tester.c

EXPANSOR_FILES	=	${SRC}/expansor.c
EXPANSOR_FILES	+=	${TESTS}/expansor_tester.c

PARSER_FILES	=	${SRC}/parser.c
PARSER_FILES	+=	${TESTS}/parser_tester.c

EXECUTOR_FILES	=	${SRC}/executor.c
EXECUTOR_FILES	+=	${TESTS}/executor_tester.c

#------------------------------------------------------------------------------
#	RULE TO GET THE .O COMPILED
#------------------------------------------------------------------------------
OBJS_LEXER		=	$(addprefix ${OBJ_DIR}/, $(notdir ${LEXER_FILES:.c=.o}))
OBJS_EXPANSOR	=	$(addprefix ${OBJ_DIR}/, $(notdir ${EXPANSOR_FILES:.c=.o}))
OBJS_PARSER		=	$(addprefix ${OBJ_DIR}/, $(notdir ${PARSER_FILES:.c=.o}))
OBJS_EXECUTOR	=	$(addprefix ${OBJ_DIR}/, $(notdir ${EXECUTOR_FILES:.c=.o}))

${OBJ_DIR}/%.o:	${SRC}/%.c ${TESTER_HEADER} Makefile
			${CC} ${CFLAGS} -c $< -o $@ ${HEADERS}

${OBJ_DIR}/%.o:	${TESTS}/%.c ${TESTER_HEADER} Makefile
			${CC} ${CFLAGS} -c $< -o $@ ${HEADERS}

#------------------------------------------------------------------------------
#	MAIN RULES TO COMPILE AND CREATE THE EXECUTABLES AND TO CLEAN THEM
#------------------------------------------------------------------------------
all:		${OBJ_DIR} ${NAME}

test:
	echo "${LEXER_FILES}"

${LEXER_TESTER}: ${OBJS_LEXER}
			@echo "Compiling $@"
			${CC} ${CFLAGS} ${HEADERS} -o $@ $^

${EXPANSOR_TESTER}: ${OBJS_EXPANSOR}
			@echo "Compiling $@"

${PARSER_TESTER}: ${OBJS_PARSER}
			@echo "Compiling $@"

${EXECUTOR_TESTER}: ${OBJS_EXECUTOR}
			@echo "Compiling $@"


clean:		
			@rm -rf ${OBJ_DIR}

fclean:		clean
			@rm -rf ${NAME}

re:			fclean all

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
