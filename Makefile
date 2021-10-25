CLIENT = client
SERVER = server

CLIENT_SRC = client.c 
SERVER_SRC = server.c
CLIENT_SRC_BONUS = client_bonus.c 
SERVER_SRC_BONUS = server_bonus.c 

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ_BONUS = $(CLIENT_SRC_BONUS:.c=.o)
SERVER_OBJ_BONUS = $(SERVER_SRC_BONUS:.c=.o)

all : $(CLIENT) $(SERVER)

$(CLIENT) : $(CLIENT_OBJ)
	@$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ)

$(SERVER) : $(SERVER_OBJ)
	@$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ)

bonus : $(CLIENT_OBJ_BONUS) $(SERVER_OBJ_BONUS)
	@$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ_BONUS)
	@$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ_BONUS)

clean:
	@$(RM) $(CLIENT_OBJ) $(CLIENT_OBJ_BONUS)
	@$(RM) $(SERVER_OBJ) $(SERVER_OBJ_BONUS)

fclean: clean
	@$(RM) $(CLIENT)
	@$(RM) $(SERVER)

re: fclean all

.PHONY: all clean fclean re bonus
