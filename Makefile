NAME				= pipex

HEADER				= ${SRCS_PATH}/pipex.h

SRCS_FILE			= pipex.c argument_parser.c error_management.c exec_cmd.c
SRCS_PATH			= ./sources
SRCS				= ${addprefix ${SRCS_PATH}/,${SRCS_FILE}}

OBJS_FILE			= ${SRCS_FILE:.c=.o}
OBJS_PATH			= ./objects
OBJS				= ${addprefix ${OBJS_PATH}/,${OBJS_FILE}}

LIBFT				= ${LIBFT_PATH}/libft.a
LIBFT_PATH			= ./libft

CC					= cc -g3 -Wall -Wextra -Werror #-fsanitize=address
REMOVE				= rm -rf

all:				${NAME}

${NAME}:			${OBJS} ${OBJS_PATH} ${LIBFT}
					${CC} ${OBJS} ${LIBFT} -o ${NAME}

${OBJS_PATH}:
					mkdir -p $@

${OBJS_PATH}/%.o:	${SRCS_PATH}/%.c ${HEADER} Makefile | ${OBJS_PATH}
					${CC} -I . -c $< -o $@

${LIBFT}:
					${MAKE} -C ${LIBFT_PATH} bonus

run:				all
					./pipex infile_ft "ping -c 3 google.com" "grep rtt" outfile_ft && cat outfile_ft

clean:
					${MAKE} -C ${LIBFT_PATH} clean
					${REMOVE} ${OBJS_PATH}

fclean:				clean
					${MAKE} -C ${LIBFT_PATH} fclean
					${REMOVE} ${NAME}

re:					fclean all

.PHONY:				all clean fclean re
