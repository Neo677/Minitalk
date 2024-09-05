CC = gcc
CFLAGS = -Wall -Werror -Wextra 
#-fPIC -no-pie

# PRINTF_PATH = ft_printf
# PRINTF_LIB = $(PRINTF_PATH)/ft_printf.a
# PRINTF_INC = -I$(PRINTF_PATH)

LIBFT_PATH = libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
LIBFT_INC = -I$(LIBFT_PATH)

SERVER = server.c
CLIENT = client.c
SERVER_EXE = $(SERVER:.c=.o)
CLIENT_EXE = $(CLIENT:.c=.o)

all: server client

server: $(SERVER_EXE) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SERVER_EXE) -o server -L$(LIBFT_PATH) -l:libft.a

client: $(CLIENT_EXE) $(PRINTF_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(CLIENT_EXE) -o client -L$(LIBFT_PATH) -l:libft.a


# server: $(SERVER_EXE) $(PRINTF_LIB) $(LIBFT_LIB)
# 	$(CC) $(CFLAGS) $(SERVER_EXE) -o server -L$(PRINTF_PATH) -l:ft_printf.a 

# client: $(CLIENT_EXE) $(PRINTF_LIB) $(LIBFT_LIB)
# 	$(CC) $(CFLAGS) $(CLIENT_EXE) -o client -L$(PRINTF_PATH) -l:ft_printf.a 

# %.o: %.c
# 	$(CC) $(CFLAGS) $(PRINTF_INC) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFT_INC) -c $< -o $@

# $(PRINTF_LIB):
# 	make -C $(PRINTF_PATH)

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
	make -C $(LIBFT_PATH)

fclean: clean
	rm -f $(SERVER_EXE) $(CLIENT_EXE) server client
	make -C $(LIBFT_PATH) fclean

# clean:
# 	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
# 	make -C $(PRINTF_PATH) $(LIBFT_PATH)

# fclean: clean
# 	rm -f $(SERVER_EXE) $(CLIENT_EXE)
# 	make -C $(PRINTF_PATH) $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re