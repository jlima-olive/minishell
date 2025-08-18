NAME = libft.a

SRC_DIR = libft/
GNL_DIR = get_next_line/

SRC_FILES = $(wildcard $(SRC_DIR)*.c) \
            $(wildcard $(GNL_DIR)*.c)

OBJ_FILES = $(SRC_FILES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@ar rcs $@ $^
	@echo "libft.a created successfully!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re