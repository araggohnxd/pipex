NAME				= pipex
NAME_BONUS			= ${NAME}_bonus

HEADER				= ${SRCS_PATH}/pipex.h
HEADER_BONUS		= ${SRCS_PATH_BONUS}/pipex_bonus.h

SRCS_FILE			= pipex.c argument_parser.c error_management.c exec_cmd.c
SRCS_PATH			= ./sources
SRCS				= ${addprefix ${SRCS_PATH}/,${SRCS_FILE}}

OBJS_FILE			= ${SRCS_FILE:.c=.o}
OBJS				= ${addprefix ${OBJS_PATH}/,${OBJS_FILE}}

SRCS_FILE_BONUS		= pipex_bonus.c argument_parser_bonus.c exec_cmd_bonus.c \
					error_management_bonus.c pipe_and_pid_bonus.c init_struct_bonus.c
SRCS_PATH_BONUS		= ${SRCS_PATH}_bonus
SRCS_BONUS			= ${addprefix ${SRCS_PATH_BONUS}/,${SRCS_FILE_BONUS}}

OBJS_FILE_BONUS		= ${SRCS_FILE_BONUS:.c=.o}
OBJS_BONUS			= ${addprefix ${OBJS_PATH}/,${OBJS_FILE_BONUS}}

OBJS_PATH			= ./objects

LIBFT				= ${LIBFT_PATH}/libft.a
LIBFT_PATH			= ./libft

CC					= cc -g3 -Wall -Wextra -Werror #-fsanitize=address
REMOVE				= rm -rf

all:				${NAME}

bonus:				${NAME_BONUS}

${NAME}:			${OBJS} ${OBJS_PATH} ${LIBFT}
					${CC} ${OBJS} ${LIBFT} -o ${NAME}

${NAME_BONUS}:		${OBJS_BONUS} ${OBJS_PATH} ${LIBFT}
					${CC} ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}

${OBJS_PATH}:
					mkdir -p $@

${OBJS_PATH}/%.o:	${SRCS_PATH}/%.c ${HEADER} Makefile | ${OBJS_PATH}
					${CC} -I . -c $< -o $@

${OBJS_PATH}/%.o:	${SRCS_PATH_BONUS}/%.c ${HEADER_BONUS} Makefile | ${OBJS_PATH}
					${CC} -I . -c $< -o $@

${LIBFT}:
					${MAKE} -C ${LIBFT_PATH} bonus

clean:
					${MAKE} -C ${LIBFT_PATH} clean
					${REMOVE} ${OBJS_PATH}

fclean:				clean
					${MAKE} -C ${LIBFT_PATH} fclean
					${REMOVE} ${NAME} ${NAME_BONUS}

re:					fclean all

.PHONY:				all clean fclean re bonus
