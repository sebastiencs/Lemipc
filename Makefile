##
## Makefile for epitech in /home/chapuis_s/rendu/
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Thu Mar  5 19:20:26 2015 chapui_s
## Last update Thu Mar  5 19:25:15 2015 chapui_s
##

NAME		= lemipc

SOURCE_DIR	= src/

SRC		= $(SOURCE_DIR)lemipc.c

OBJ		= $(SRC:.c=.o)

INCLUDES	= includes/

CFLAGS		= -Wall -Wextra -I $(INCLUDES)

CC		= gcc

RM		= rm -f

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
