NAME = philo
SRC = main.c actions.c checks.c start.c threads.c utils.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ)

	@${CC} ${SRC} -o ${NAME}
	
clean :
		@${RM} ${OBJ}

fclean : clean

		@${RM} ${OBJ}

re: fclean all

.PHONY: all clean fclean re
