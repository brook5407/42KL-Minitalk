SRCS	= client.c server.c
SRCSB	= client_bonus.c server_bonus.c

LIBFT	= libft/libft.a

CC		= gcc -g3
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address
RM		= rm -f

all:	server client

bonus:	server_bonus client_bonus

server: ${LIBFT}
		${CC} ${CFLAGS} $@.c $< -o $@

client: ${LIBFT}
		${CC} ${CFLAGS} $@.c $< -o $@

server_bonus: ${LIBFT}
		${CC} ${CFLAGS} $@.c $< -o $@

client_bonus: ${LIBFT}
		${CC} ${CFLAGS} $@.c $< -o $@

${LIBFT}:
		make -C libft

clean:
		make -C libft clean

fclean:	clean
		${RM} server client server_bonus client_bonus libft/*.a

re:	fclean all

.PHONY: all bonus libft clean fclean re
