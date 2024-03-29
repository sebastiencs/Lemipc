##
## Makefile for epitech in /home/chapuis_s/rendu/
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Thu Mar  5 19:20:26 2015 chapui_s
## Last update Sun Mar  8 18:06:07 2015 chapui_s
##

NAME		= lemipc

SOURCE_DIR	= src/

SRC		= $(SOURCE_DIR)lemipc.c			\
		  $(SOURCE_DIR)get_map.c		\
		  $(SOURCE_DIR)get_sem.c		\
		  $(SOURCE_DIR)get_msg.c		\
		  $(SOURCE_DIR)move.c			\
		  $(SOURCE_DIR)move_random.c		\
		  $(SOURCE_DIR)access_battlefield.c	\
		  $(SOURCE_DIR)access_connected.c	\
		  $(SOURCE_DIR)can_i_fight.c		\
		  $(SOURCE_DIR)find_and_fuck.c		\
		  $(SOURCE_DIR)is_enemy_still_there.c	\
		  $(SOURCE_DIR)msgq.c			\
		  $(SOURCE_DIR)prepare_battle.c		\
		  $(SOURCE_DIR)sem.c			\
		  $(SOURCE_DIR)set_win.c		\
		  $(SOURCE_DIR)prepare_sdl.c		\
		  $(SOURCE_DIR)print_battlefield.c	\
		  $(SOURCE_DIR)print_battlefield_sdl.c	\
		  $(SOURCE_DIR)get_args.c

OBJ		= $(SRC:.c=.o)

INCLUDES	= ./include/

ifdef CFLAGS
	SDL	= -lSDL
endif

override CFLAGS	+= -Wall -Wextra $(SDL) -I $(INCLUDES)

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
