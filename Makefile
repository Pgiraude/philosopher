NAME =	philo

HEADER	=	philo.h

SRC	=	philo.c error_manager.c init_philo.c \
		launch_philo.c exit_philo.c utils_philo.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Werror -Wextra -Wall

CC	=	cc

RM	=	rm -f

%.o : %.c ${HEADER}
	${CC} ${CFLAGS} -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) -pthread $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
