LIB_DIR=	libft/
GNL_DIR=	get_next_line/

SRC_FILES=  $(wildcard ${LIB_DIR}*.c) \
			$(wildcard ${GNL_DIR}*.c) \

OBJ_FILES=	${SRC_FILES:.c=.o}

NAME=		../jojo_libft.a

HDR_FILE=	libft.h

CC=			cc

FLAGS=		-Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJ_FILES}
	ar rcs $@ $?

%.o: %.c ${HDR_FILE}
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

clean: 
	rm -f $(OBJ_BONUS) $(OBJ_FILES) 
	@rm -f .bonus

fclean: clean 
	rm -f ${NAME}

fcleanlocal:
	rm -f ${NAME}

re: fclean all

.PHONY: re fclean clean all