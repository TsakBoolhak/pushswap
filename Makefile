SRCS		= main.c \
			instructions1.c \
			instructions2.c \
			minmax.c \
			sorted_array.c

OBJS		= ${SRCS:.c=.o}

NAME		= push_swap

CC			= @gcc

CFLAGS		= -g3 -Wall -Wextra -Wpedantic -Werror -I./libft -I.

RM			= rm -f

.c.o		= ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS}
			make -C ./libft
			${CC} ${CFLAGS} ${OBJS} -o ${NAME} -L./libft -lft

all:			${NAME}

clean:
			make clean -C ./libft
				@${RM} ${OBJS}

fclean:			clean
			make fclean -C ./libft
			@${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re

