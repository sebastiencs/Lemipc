/*
** lemipc.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  5 19:24:41 2015 chapui_s
** Last update Sat Mar  7 22:51:10 2015 chapui_s
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

void		mod_connected(t_info *info, int set)
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
  mod_connected(info, ONE_MORE);
  info->i_am_alive = 1;
  printf("Ready to fight !\n");
  return (0);
}

int		main(int argc, char **argv)
{
  t_info	info;

  if (get_info(argc, argv, &info) == -1)
    return (-1);
  if (prepare_for_battle(&info) == -1)
    return (-1);
  /* while (AM_I_ALIVE) */
  /* { */

  /* } */
  return (0);
}
