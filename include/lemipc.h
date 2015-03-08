/*
** lemipc.h for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  5 19:27:16 2015 chapui_s
** Last update Sun Mar  8 18:08:09 2015 chapui_s
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
# include <unistd.h>
# include <errno.h>
# include <time.h>
# include <string.h>
# include <signal.h>

# ifdef SDL_OUTPUT
#  include <SDL/SDL.h>
# endif /* !SDL_OUTPUT */

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
  char		*map;
# ifdef SDL_OUTPUT
  SDL_Surface	*screen;
  SDL_Surface	*player;
  Uint32	colors[5];
  Uint32	black;
# endif /* !SDL_OUTPUT */
}		t_info;

typedef struct	s_enemy
{
  int		x;
  int		y;
}		t_enemy;

typedef struct	s_func_rand
{
  int		nb;
  int		(*func)(t_info *info, int *x, int *y);
}		t_func_rand;

# define TEAM_NUMBER_DEFAULT	(1)
# define PATH_DEFAULT		(".")

# define ONE_MORE		(1)
# define ONE_LESS		(-1)

# ifndef SDL_OUTPUT
#  define SIZE_X		((int)(20 * sizeof(char)))
#  define SIZE_Y		((int)(20 * sizeof(char)))
#  define RUN_TO_WIN		(8)
#  define TIME_TO_SLEEP		(1000000)
# else /* !SDL_OUTPUT */
#  define SIZE_X		((int)(100 * sizeof(char)))
#  define SIZE_Y		((int)(100 * sizeof(char)))
#  define RUN_TO_WIN		(30)
#  define TIME_TO_SLEEP		(100000)
# endif /* !SDL_OUTPUT */

# define SIZE_MAP		(SIZE_X * SIZE_Y)

# define SIZE_SPACE		(sizeof(int) + sizeof(char*) + SIZE_MAP)

# define KEEP_FIRST		(info.is_first && get_connected(&info))
# define AM_I_ALIVE		(info.i_am_alive == 1 || KEEP_FIRST)

# define ABS(x)	(x < 0) ? (-x) : (x)

int		get_info(int argc, char **argv, t_info *info);
int		get_map(t_info *info);
int		get_sem(t_info *info);
int		get_msg(t_info *info);
void		move(t_info *info, int *x, int *y, t_enemy *asshole);
void		move_random(t_info *info, int *x, int *y);
int		is_busy(t_info *info, int x, int y);
void		sem_lock(t_info *info);
void		sem_unlock(t_info *info);
void		set_connected(t_info *info, int set);
int		get_connected(t_info *info);
char		get_battlefield(t_info *info, int x, int y);
void		set_battlefield(t_info *info, int x, int y, char value);
int		prepare_for_battle(t_info *info);
int		get_msgq(t_info *info,
			 int msg_id,
			 int team_number,
			 t_msg *msg);
void		send_msgq(t_info *info, t_msg *msg);
int		is_enemy_still_there(t_info *info,
				     t_enemy *stupid_guy,
				     char *s);
int		find_enemy_and_fuck_him(t_info *info);
int		can_i_fight(t_info *info);
void		down_the_arms(t_info *info);
void		print_battlefield(t_info *info);
int		set_win(t_info *info, int *nb_free);
void		prepare_sdl(t_info *info);

#endif /* !LEMIPC_H_ */
