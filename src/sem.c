/*
** sem.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 08:21:16 2015 chapui_s
** Last update Sun Mar  8 21:41:29 2015 chapui_s
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
