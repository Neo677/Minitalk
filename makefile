SOURCE = server.c client.c
OBJECT = $(SOURCE:.c=.o)
CC = gcc 
CFLAGS = -Wall -Werror -Wextra -fPIC

all : server client

server: server.o printf/ft_printf
	$(CC) -o $@ $< printf/ft_printf -pie

client: client.o printf/ft_printf
	$(CC) -o $@ $< printf/ft_printf -pie

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

printf/ft_printf:
	make -C printf

clean : 
	rm -r $(OBJECT)
	make -C printf clean

fclean : clean
	rm -f server client printf/ft_printf

re : fclean all

.PHONY : all printf clean fclean re
