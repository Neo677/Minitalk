CC = gcc
CFLAGS = -Wall -Werror -Wextra -fPIC -no-pie

PRINTF_PATH = ft_printf
PRINTF_LIB = $(PRINTF_PATH)/ft_printf.a
PRINTF_INC = -I$(PRINTF_PATH)

SERVER = server.c
CLIENT = client.c
SERVER_EXE = $(SERVER:.c=.o)
CLIENT_EXE = $(CLIENT:.c=.o)

all: server client

server: $(SERVER_EXE) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(SERVER_EXE) -o server -L$(PRINTF_PATH) -l:ft_printf.a

client: $(CLIENT_EXE) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(CLIENT_EXE) -o client -L$(PRINTF_PATH) -l:ft_printf.a

%.o: %.c
	$(CC) $(CFLAGS) $(PRINTF_INC) -c $< -o $@

$(PRINTF_LIB):
	make -C $(PRINTF_PATH)

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
	make -C $(PRINTF_PATH)

fclean: clean
	rm -f $(SERVER_EXE) $(CLIENT_EXE)
	make -C $(PRINTF_PATH) fclean

re: fclean all

.PHONY: all clean fclean re