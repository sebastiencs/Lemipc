/*
** lemipc.h for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  5 19:27:16 2015 chapui_s
** Last update Sun Mar  8 05:42:44 2015 chapui_s
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

# include <stdio.h>
# include <stdlib.h>
# include <sys/ipc.h>
# include <sys/types.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <sys/msg.h>
# include <errno.h>
# include <time.h>
# include <string.h>


// TO RM
int is_existing;

typedef struct	s_space
{
  int		nb_connected;
  char		*map;
}		t_space;

typedef struct	s_msg
{
  long		mtype;
  char		str[10];
}		t_msg;

typedef struct	s_info
{
  char		*path;
  char		team_number;
  int		is_first;
  key_t		key;
  int		shm_id;
  int		sem_id;
  int		msg_id;
  t_space	*space;
  int		i_am_alive;
  int		x;
  int		y;
}		t_info;

typedef struct	s_enemy
{
  int		x;
  int		y;
}		t_enemy;

# define TEAM_NUMBER_DEFAULT	(1)
# define PATH_DEFAULT		(".")

# define ONE_MORE		(1)
# define ONE_LESS		(-1)

# define SIZE_X			((int)(20 * sizeof(char)))
# define SIZE_Y			((int)(20 * sizeof(char)))
# define SIZE_MAP		(SIZE_X * SIZE_Y)

# define SIZE_SPACE		(sizeof(int) + sizeof(char*) + SIZE_MAP)

# define KEEP_FIRST		(info.is_first && get_connected(&info))
# define AM_I_ALIVE		(info.i_am_alive == 1 || KEEP_FIRST)

#define ABS(x)	(x < 0) ? (-x) : (x)

int		get_info(int argc, char **argv, t_info *info);
int		get_map(t_info *info);
int		get_sem(t_info *info);
int		get_msg(t_info *info);
void		move(t_info *info, int *x, int *y, t_enemy *asshole);

#endif /* !LEMIPC_H_ */
