CC = cc
SERVER = server
CLIENT = client
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3 

SERVER_SRC = server.c minitalk_utils.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_SRC = client.c minitalk_utils.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

SERVER_BONUS_SRC = server_bonus.c minitalk_utils_bonus.c
SERVER_BONUS_OBJ = $(SERVER_BONUS_SRC:.c=.o)

CLIENT_BONUS_SRC = client_bonus.c minitalk_utils_bonus.c
CLIENT_BONUS_OBJ = $(CLIENT_BONUS_SRC:.c=.o)

all: clean $(SERVER) $(CLIENT) 

$(SERVER): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(LIBFT) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LIBFT) -o $(CLIENT)

server_bonus: $(SERVER_BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJ) $(LIBFT) -o server_bonus

client_bonus: $(CLIENT_BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJ) $(LIBFT) -o client_bonus


$(LIBFT):
	make -C $(LIBFT_DIR) 
	make -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: server_bonus client_bonus

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) $(SERVER_BONUS_OBJ) $(CLIENT_BONUS_OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT) client_bonus server_bonus
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re