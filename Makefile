CC = cc
SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3 
UTILS_SRC = minitalk_utils.c
SERVER_SRC = server.c $(UTILS_SRC)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_SRC = client.c $(UTILS_SRC)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Bonus
SERVER_BONUS_SRC = server_bonus.c $(UTILS_SRC)
SERVER_BONUS_OBJ = $(SERVER_BONUS_SRC:.c=.o)

CLIENT_BONUS_SRC = client_bonus.c $(UTILS_SRC)
CLIENT_BONUS_OBJ = $(CLIENT_BONUS_SRC:.c=.o)

all: $(SERVER) $(CLIENT) 

$(SERVER): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(LIBFT) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LIBFT) -o $(CLIENT)

$(SERVER_BONUS): $(SERVER_BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJ) $(LIBFT) -o $(SERVER_BONUS)

$(CLIENT_BONUS): $(CLIENT_BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJ) $(LIBFT) -o $(CLIENT_BONUS)

$(LIBFT):
	make -C $(LIBFT_DIR) 
	make -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) $(SERVER_BONUS_OBJ) $(CLIENT_BONUS_OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re