# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomtom <tomtom@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/07 18:12:06 by thobenel          #+#    #+#              #
#    Updated: 2024/09/11 16:54:19 by tomtom           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT_PATH = libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
LIBFT_INC = -I$(LIBFT_PATH)

SERVER = server.c
CLIENT = client.c
SERVER_EXE = $(SERVER:.c=.o)
CLIENT_EXE = $(CLIENT:.c=.o)

# Couleurs
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

all: server client

server: $(SERVER_EXE) $(LIBFT_LIB)
	@echo "$(YELLOW)Compiling server...$(RESET)"
	$(CC) $(CFLAGS) $(SERVER_EXE) -o server -L$(LIBFT_PATH) -lft
	@echo "$(GREEN)Server compilation complete!$(RESET)"

client: $(CLIENT_EXE) $(LIBFT_LIB)
	@echo "$(YELLOW)Compiling client...$(RESET)"
	$(CC) $(CFLAGS) $(CLIENT_EXE) -o client -L$(LIBFT_PATH) -lft
	@echo "$(GREEN)Client compilation complete!$(RESET)"

%.o: %.c
	@echo "$(BLUE)Compiling $< into object file...$(RESET)"
	$(CC) $(CFLAGS) $(LIBFT_INC) -c $< -o $@

$(LIBFT_LIB):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	make -C $(LIBFT_PATH)
	@echo "$(GREEN)Libft compilation complete!$(RESET)"

clean:
	@echo "$(RED)Cleaning up object files...$(RESET)"
	rm -f $(SERVER_EXE) $(CLIENT_EXE)
	make -C $(LIBFT_PATH) clean
	@echo "$(RED)Clean complete!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executables...$(RESET)"
	rm -f server client
	make -C $(LIBFT_PATH) fclean
	@echo "$(RED)Full clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re


# CC = cc
# CFLAGS = -Wall -Werror -Wextra

# # PRINTF_PATH = ft_printf
# # PRINTF_LIB = $(PRINTF_PATH)/ft_printf.a
# # PRINTF_INC = -I$(PRINTF_PATH)

# LIBFT_PATH = libft
# LIBFT_LIB = $(LIBFT_PATH)/libft.a
# LIBFT_INC = -I$(LIBFT_PATH)

# SERVER = server.c
# CLIENT = client.c
# SERVER_EXE = $(SERVER:.c=.o)
# CLIENT_EXE = $(CLIENT:.c=.o)


# all: server client

# server: $(SERVER_EXE) $(LIBFT_LIB)
# 	$(CC) $(CFLAGS) $(SERVER_EXE) -o server -L$(LIBFT_PATH) -lft

# client: $(CLIENT_EXE) $(LIBFT_LIB)
# 	$(CC) $(CFLAGS) $(CLIENT_EXE) -o client -L$(LIBFT_PATH) -lft


# # server: $(SERVER_EXE) $(PRINTF_LIB) $(LIBFT_LIB)
# # 	$(CC) $(CFLAGS) $(SERVER_EXE) -o server -L$(PRINTF_PATH) -l:ft_printf.a 

# # client: $(CLIENT_EXE) $(PRINTF_LIB) $(LIBFT_LIB)
# # 	$(CC) $(CFLAGS) $(CLIENT_EXE) -o client -L$(PRINTF_PATH) -l:ft_printf.a 

# # %.o: %.c
# # 	$(CC) $(CFLAGS) $(PRINTF_INC) -c $< -o $@

# %.o: %.c
# 	$(CC) $(CFLAGS) $(LIBFT_INC) -c $< -o $@

# # $(PRINTF_LIB):
# # 	make -C $(PRINTF_PATH)

# $(LIBFT_LIB):
# 	make -C $(LIBFT_PATH)

# clean:
# 	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
# 	make -C $(LIBFT_PATH) clean

# fclean: clean
# 	rm -f $(SERVER_EXE) $(CLIENT_EXE) server client
# 	make -C $(LIBFT_PATH) fclean

# # clean:
# # 	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
# # 	make -C $(PRINTF_PATH) $(LIBFT_PATH)

# # fclean: clean
# # 	rm -f $(SERVER_EXE) $(CLIENT_EXE)
# # 	make -C $(PRINTF_PATH) $(LIBFT_PATH) fclean

# re: fclean all

# .PHONY: all clean fclean re
