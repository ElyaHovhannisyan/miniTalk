NAME1	= client
NAME2	= server
SRCS	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))
CC		= gcc
FLAGS	= -Wall -Wextra -Werror
RM		= rm -f

%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@

all: $(NAME1) $(NAME2)

NAME1: $(OBJS)
		$(CC) $(FLAGS) client.o -o $(NAME1)

NAME2: $(OBJS)
		$(CC) $(FLAGS) server.o -o $(NAME2)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME1) $(NAME2)

re: fclean all

.PHONY: all clean fclean re
