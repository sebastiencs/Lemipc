/*
** lemipc.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  5 19:24:41 2015 chapui_s
** Last update Sun Mar  8 01:05:32 2015 chapui_s
*/

#include "lemipc.h"

void			sem_lock(t_info *info)
{
  struct sembuf		sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = -1;
  semop(info->sem_id, &sops, 1);
}

void			sem_unlock(t_info *info)
{
  struct sembuf		sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = 1;
  semop(info->sem_id, &sops, 1);
}

void		set_connected(t_info *info, int set)
{
  sem_lock(info);
  info->space->nb_connected += set;
  sem_unlock(info);
}

int		get_connected(t_info *info)
{
  int		tmp;

  sem_lock(info);
  tmp = info->space->nb_connected;
  sem_unlock(info);
  return (tmp);
}

void		down_the_arms(t_info *info)
{
  if (info->is_first && !(get_connected(info)))
  {
    msgctl(info->msg_id, IPC_RMID, (struct msqid_ds*)0);
    semctl(info->sem_id, 1, IPC_RMID);
    shmctl(info->shm_id, IPC_RMID, (struct shmid_ds*)0);
  }
}

char		get_battlefield(t_info *info, int x, int y)
{
  char		tmp;

  x = (x < 0) ? (0) : (x % SIZE_X);
  y = (y < 0) ? (0) : (y % SIZE_Y);
  sem_lock(info);
  tmp = info->space->map[(y * SIZE_Y + x) % SIZE_MAP];
  sem_unlock(info);
  return (tmp);
}

void		set_battlefield(t_info *info, int x, int y, char value)
{
  x = (x < 0) ? (0) : (x % SIZE_X);
  y = (y < 0) ? (0) : (y % SIZE_Y);
  sem_lock(info);
  info->space->map[(y * SIZE_Y + x) % SIZE_MAP] = value;
  sem_unlock(info);
}

void		place_this_spartiate(t_info *info)
{
  int		x;
  int		y;

  x = rand() % SIZE_X;
  y = rand() % SIZE_Y;
  while (get_battlefield(info, x, y) != 0)
  {
    x += 1;
    if (!(x % SIZE_X))
      y += 1;
  }
  info->x = x % SIZE_X;
  info->y = y % SIZE_Y;
  set_battlefield(info, x, y, info->team_number);
}

int		prepare_for_battle(t_info *info)
{
  if (get_map(info) == -1)
    return (-1);
  if (get_sem(info) == -1)
    return (-1);
  if (get_msg(info) == -1)
    return (-1);
  if (get_connected(info) > (int)SIZE_MAP / 2)
  {
    printf("Ouch.. They block the door :-O I can't go in !\n");
    printf("Let me go home ! *call his mother*\n");
    down_the_arms(info);
    return (-1);
  }
  set_connected(info, ONE_MORE);
  info->i_am_alive = 1;
  place_this_spartiate(info);
#ifdef DEBUG
  printf("Ready to fight ! x: %d y: %d Give me wine !\n", info->x, info->y);
#else
  printf("Ready to fight ! Give me wine and whores !\n");
#endif
  return (0);
}

int		am_i_surrounded(t_info *info, int nb_attackers)
{
  int		x;
  int		id;

  x = ((info->x - 1) < 0) ? (0) : (info->x - 1);
  while (x < info->x + 1 && x < SIZE_X)
  {
    if (info->y + 1 < SIZE_Y)
      if ((id = get_battlefield(info, x, info->y + 1)) != 0
	  && id != info->team_number)
	nb_attackers += 1;
    if (info->y - 1 >= 0)
      if ((id = get_battlefield(info, x, info->y - 1)) != 0
	  && id != info->team_number)
	nb_attackers += 1;
    x += 1;
  }
  if (info->x > 0 && (id = get_battlefield(info, info->x - 1, info->y)) != 0
      && id != info->team_number)
    nb_attackers += 1;
  if (info->x < SIZE_X - 1
      && (id = get_battlefield(info, info->x + 1, info->y)) != 0
      && id != info->team_number)
    nb_attackers += 1;
  return ((nb_attackers >= 2) ? (1) : (0));
}

int		can_i_fight(t_info *info)
{
  if (info->i_am_alive && am_i_surrounded(info, 0))
  {
    info->i_am_alive = 0;
    printf("FUCK ! They killed me ! It wasn't my war !\n");
    return (0);
  }
  else if (info->i_am_alive)
  {
    printf("Still alive !\n");
    return (1);
  }
  return (0);
}

int		main(int argc, char **argv)
{
  t_info	info;

  if (get_info(argc, argv, &info) == -1)
    return (-1);
  srand(time((time_t*)0));
  if (prepare_for_battle(&info) == -1)
    return (-1);
  while (AM_I_ALIVE)
  {
    if (can_i_fight(&info))
    {
      // faut parler avec les autres de l'equipe et aller dans une direction
      break ;
    }
    break ;
  }
  // Ca faudra l'enlever
  if (is_existing)
  {
    msgctl(info.msg_id, IPC_RMID, (struct msqid_ds*)0);
    semctl(info.sem_id, 1, IPC_RMID);
    shmctl(info.shm_id, IPC_RMID, (struct shmid_ds*)0);
  }
  return (0);
}
