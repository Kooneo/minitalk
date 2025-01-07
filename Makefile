CC = cc
SERVER = server
CLIENT = client
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3 

SERVER_SRC = server.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_SRC = client.c 
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

all: fclean $(SERVER) $(CLIENT) 

$(SERVER): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(LIBFT) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LIBFT) -o $(CLIENT)

$(LIBFT):
	make -C $(LIBFT_DIR) 
	make -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OFILES)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) $(SERVER) $(CLIENT)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re