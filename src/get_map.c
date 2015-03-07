/*
** get_map.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  7 15:16:28 2015 chapui_s
** Last update Sat Mar  7 22:11:54 2015 chapui_s
*/

#include "lemipc.h"

static int	get_existing(t_info *info)
{
  printf("Using segment %d\n", info->shm_id);
  if ((info->space = (t_space*)shmat(info->shm_id,
				     (const void*)0,
				     SHM_R | SHM_W))
      == (void*)-1)
  {
    fprintf(stderr, "ERROR: shmat: %s\n", strerror(errno));
    return (-1);
  }
  info->is_first = 0;
  shmctl(info->shm_id, IPC_RMID, NULL);
  return (0);
}

static int	get_creat(t_info *info)
{
  printf("Creating segment %d\n", info->shm_id);
  if ((info->space = (t_space*)shmat(info->shm_id,
				     (const void*)0,
				     SHM_R | SHM_W))
      == (void*)-1)
  {
    fprintf(stderr, "ERROR: shmat: %s\n", strerror(errno));
    return (-1);
  }
  info->space->nb_connected = 0;
  info->is_first = 1;
  info->space->map = (char*)(&(info->space->map) + 1);
  bzero(info->space->map, SIZE_MAP);
  return (0);
}

static int	error(void)
{
  printf("ERROR: shmget: %s\n", strerror(errno));
  return (-1);
}

int		get_map(t_info *info)
{
  if ((info->shm_id = shmget(info->key, SIZE_SPACE, SHM_R | SHM_W)) != -1)
  {
    return (get_existing(info));
  }
  else if ((info->shm_id = shmget(info->key, SIZE_SPACE,
				  IPC_CREAT | SHM_R | SHM_W)) != -1)
  {
    return (get_creat(info));
  }
  else
  {
    return (error());
  }
}
