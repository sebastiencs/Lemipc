/*
** lemipc.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar  5 19:24:41 2015 chapui_s
** Last update Sun Mar  8 17:34:29 2015 chapui_s
*/

#include "lemipc.h"

void		manage_sig(t_info *param)
{
  static t_info *info;

  if (!param && info)
  {
    msgctl(info->msg_id, IPC_RMID, (struct msqid_ds*)0);
    semctl(info->sem_id, 1, IPC_RMID);
    shmctl(info->shm_id, IPC_RMID, (struct shmid_ds*)0);
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

#ifdef SDL_OUTPUT

void		prepare_sdl(t_info *info)
{
  if (SDL_Init(SDL_INIT_VIDEO))
  {
    fprintf(stderr, "Warning: Can't initialize SDL: %s\n", SDL_GetError());
  }
  if (!(info->screen = SDL_SetVideoMode(400, 400, 32, SDL_HWSURFACE)))
  {
    SDL_Quit();
  }
  if (!(info->player = SDL_CreateRGBSurface(SDL_HWSURFACE,
					    20, 20, 32, 0, 0, 0, 0)))
  {
    SDL_FreeSurface(info->screen);
    SDL_Quit();
  }
  SDL_WM_SetCaption("LemIPC !", (const char*)0);
  info->colors[0] = SDL_MapRGB(info->screen->format, 255, 0, 0);
  info->colors[1] = SDL_MapRGB(info->screen->format, 30, 144, 255);
  info->colors[2] = SDL_MapRGB(info->screen->format, 69, 139, 0);
  info->colors[3] = SDL_MapRGB(info->screen->format, 202, 255, 112);
  info->colors[4] = SDL_MapRGB(info->screen->format, 0, 0, 0);
  info->black = SDL_MapRGB(info->screen->format, 0, 0, 0);
}

#endif

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
    sleep(1);
  }
  destroy(&info);
  return (0);
}
