SOURCES = server.c client.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIE

all: server client

server: server.o ft_printf/libftprintf.a
	$(CC) -o $@ $< -Lft_printf -lftprintf

client: client.o ft_printf/libftprintf.a
	$(CC) -o $@ $< -Lft_printf -lftprintf

%.o: %.c
	$(CC) -c $(CFLAGS) $<

ft_printf/libftprintf.a:
	make -C ft_printf

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C ft_printf clean
	
fclean: clean
	rm -f server client ft_printf/libftprintf.a

re: fclean all

.PHONY: all clean fclean re