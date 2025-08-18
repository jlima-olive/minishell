NAME = pipex
BONUS_NAME = pipex_bonus
LIBFT_DIR = ../my_libft

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SRC = pipex.c pipex_func.c check_input.c
OBJ = $(SRC:.c=.o)

BONUS_SRC = pipex_bonus.c pipex_func.c check_input.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(AR) $(NAME).a $(OBJ)
	@$(CC) $(CFLAGS) $(NAME).c $(NAME).a $(LIBFT_DIR)/libft.a -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(AR) $(BONUS_NAME).a $(BONUS_OBJ)
	@$(CC) $(CFLAGS) $(BONUS_NAME).c $(BONUS_NAME).a $(LIBFT_DIR)/libft.a -o $(BONUS_NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME) $(NAME).a $(BONUS_NAME).a

re: fclean all

.PHONY: all bonus clean fclean re