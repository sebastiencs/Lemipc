/*
** get_sem.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  7 15:33:34 2015 chapui_s
** Last update Sat Mar  7 22:33:25 2015 chapui_s
*/

#include "lemipc.h"

static int	get_existing(t_info *info)
{
  printf("Using semaphore %d\n", info->sem_id);
  semctl(info->sem_id, 1, IPC_RMID);
  return (0);
}

static int	get_creat(t_info *info)
{
  printf("Creating semaphore %d\n", info->sem_id);
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
