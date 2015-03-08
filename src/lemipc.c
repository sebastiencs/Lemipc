/*
** lemipc.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  5 19:24:41 2015 chapui_s
** Last update Sun Mar  8 23:08:12 2015 chapui_s
*/

#include "lemipc.h"

void		manage_sig(t_info *param)
{
  static t_info *info;

  if (!param && info)
  {
    if (info->is_first)
    {
      msgctl(info->msg_id, IPC_RMID, (struct msqid_ds*)0);
      semctl(info->sem_id, 1, IPC_RMID);
      shmctl(info->shm_id, IPC_RMID, (struct shmid_ds*)0);
    }
    else
    {
      set_connected(info, ONE_LESS);
      sem_lock(info);
      info->map[(info->y * SIZE_Y + info->x) % SIZE_MAP] = 0;
      sem_unlock(info);
    }
  }
  else
    info = param;
}

void		sig_handler(int sig)
{
  (void)sig;
  manage_sig((t_info*)0);
  exit(0);
}

void		destroy(t_info *info)
{
  if (info->is_first)
  {
    msgctl(info->msg_id, IPC_RMID, (struct msqid_ds*)0);
    semctl(info->sem_id, 1, IPC_RMID);
    shmctl(info->shm_id, IPC_RMID, (struct shmid_ds*)0);
#ifdef SDL_OUTPUT
    SDL_FreeSurface(info->player);
    SDL_FreeSurface(info->screen);
    SDL_Quit();
#endif
  }
}

int		main(int argc, char **argv)
{
  t_info	info;

  signal(SIGINT, sig_handler);
  if (get_info(argc, argv, &info) == -1)
    return (-1);
  manage_sig(&info);
  if (prepare_for_battle(&info) == -1)
    return (-1);
#ifdef SDL_OUTPUT
  if (info.is_first)
    prepare_sdl(&info);
#endif
  manage_sig(&info);
  while (AM_I_ALIVE)
  {
    if (can_i_fight(&info))
    {
      find_enemy_and_fuck_him(&info);
    }
    if (info.is_first)
      print_battlefield(&info);
    usleep(TIME_TO_SLEEP);
  }
  destroy(&info);
  return (0);
}
