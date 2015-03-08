/*
** get_sem.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  7 15:33:34 2015 chapui_s
** Last update Sun Mar  8 21:40:35 2015 chapui_s
*/

#include "lemipc.h"

static int	get_existing(t_info *info)
{
#ifdef DEBUG
  printf("Using semaphore %d\n", info->sem_id);
#else
  printf("I already brought my sword, get out of my way bitch\n");
#endif
  if (info->is_first)
    semctl(info->sem_id, 0, SETVAL, 1);
  return (0);
}

static int	get_creat(t_info *info)
{
#ifdef DEBUG
  printf("Creating semaphore %d\n", info->sem_id);
#else
  printf("This sword looks good *rip off it from a dead man and rape him*\n");
#endif
  semctl(info->sem_id, 0, SETVAL, 1);
  return (0);
}

static int	error(void)
{
  printf("ERROR: semget: %s\n", strerror(errno));
  return (-1);
}

int		get_sem(t_info *info)
{
  if ((info->sem_id = semget(info->key, 1, SHM_R | SHM_W)) != -1)
  {
    return (get_existing(info));
  }
  else if ((info->sem_id = semget(info->key, 1,
				  IPC_CREAT | SHM_R | SHM_W)) != -1)
  {
    return (get_creat(info));
  }
  else
  {
    return (error());
  }
}
