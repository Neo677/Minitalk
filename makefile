SOURCE = server.c client.c
OBJECT = $(SOURCE:.c=.o)
CC = gcc 
CFLAGS = -Wall -Werror -Wextra  

all : server client

server: server.o printf/ft_printf.a
	$(CC) -o $@ $< printf/ft_printf.a

client: client.o printf/ft_printf.a
	$(CC) -o $@ $< printf/ft_printf.a

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

printf/ft_printf.a:
	make -C printf

clean : 
	rm -r $(OBJECT)
	make -C printf clean

fclean : clean
	rm -f server client printf/ft_printf.a

re : fclean all

.PHONY : all printf clean fclean re
