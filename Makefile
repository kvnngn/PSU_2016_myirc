##
## Makefile for PSU_2016_myftp in /home/kevin/rendu/PSU_2016_myftp
## 
## Made by kevin
## Login   <kevin3.nguyen@epitech.eu>
## 
## Started on  Tue May  9 14:18:40 2017 kevin
## Last update Sun Jun 11 17:56:15 2017 Muratore Valentin
##

RM      = rm -f

NAME    = server

NAME2    = client

CFLAGS += -Wall -Wextra -Werror -g3
CFLAGS += -I./include

SRC	= src/server.c \
	  src/tools.c \
	  src/cmd_nick.c \
	  src/cmd_server.c \
	  src/cmd_server2.c \
	  src/cmd_server3.c \

SRC2	= src/client.c \
	  src/tools.c \
	  src/cmd_client.c

OBJ    = $(SRC:.c=.o)

OBJ2    = $(SRC2:.c=.o)

all: $(NAME) $(NAME2)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) -L./lib 

$(NAME2): $(OBJ2)
	gcc $(OBJ2) -o $(NAME2) -L./lib 

clean:
	$(RM) $(OBJ) $(OBJ2)

fclean: clean
	$(RM) $(NAME) $(NAME2)

re: fclean all

.PHONY: all clean fclean re
