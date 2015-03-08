##
## Makefile for epitech in /home/chapuis_s/rendu/
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Thu Mar  5 19:20:26 2015 chapui_s
## Last update Sun Mar  8 05:44:24 2015 chapui_s
##

NAME		= lemipc

SOURCE_DIR	= src/

SRC		= $(SOURCE_DIR)lemipc.c		\
		  $(SOURCE_DIR)get_map.c	\
		  $(SOURCE_DIR)get_sem.c	\
		  $(SOURCE_DIR)get_msg.c	\
		  $(SOURCE_DIR)move.c		\
		  $(SOURCE_DIR)get_args.c

OBJ		= $(SRC:.c=.o)

INCLUDES	= ./include/

CFLAGS		= -Wall -Wextra -ggdb -I $(INCLUDES)

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
