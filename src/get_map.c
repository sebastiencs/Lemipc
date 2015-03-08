/*
** get_map.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  7 15:16:28 2015 chapui_s
** Last update Sun Mar  8 09:05:30 2015 chapui_s
*/

#include "lemipc.h"

static int	get_existing(t_info *info)
{
#ifdef DEBUG
  printf("Using segment %d\n", info->shm_id);
#else
  printf("I won't let you die, not in this battle, not int this war\n");
#endif
  if ((info->space = (t_space*)shmat(info->shm_id,
				     (const void*)0,
				     SHM_R | SHM_W))
      == (void*)-1)
  {
    fprintf(stderr, "ERROR: shmat: %s\n", strerror(errno));
    return (-1);
  }
  info->is_first = 0;
  info->map = (char*)(&(info->space->map) + 1);
  return (0);
}

static int	get_creat(t_info *info)
{
#ifdef DEBUG
  printf("Creating segment %d\n", info->shm_id);
#else
  printf("WAR DECLARATION !\n");
#endif
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
  info->map = (char*)(&(info->space->map) + 1);
  bzero(info->map, SIZE_MAP);
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
