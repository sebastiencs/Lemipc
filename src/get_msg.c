/*
** get_msg.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sat Mar  7 15:40:57 2015 chapui_s
** Last update Sun Mar  8 00:36:43 2015 chapui_s
*/

#include "lemipc.h"

static int	get_existing(t_info *info)
{
#ifdef DEBUG
  printf("Using msgq %d\n", info->msg_id);
#else
  (void)info;
  printf("Your mother gave me this shield after I fucked her !\n");
#endif
  return (0);
}

static int	get_creat(t_info *info)
{
#ifdef DEBUG
  printf("Creating msgq %d\n", info->msg_id);
#else
  (void)info;
  printf("Give me a shield ! Give me a shield !\n");
#endif
  return (0);
}

static int	error(void)
{
  printf("ERROR: semget: %s\n", strerror(errno));
  return (-1);
}

int		get_msg(t_info *info)
{
  if ((info->msg_id = msgget(info->key, SHM_R | SHM_W)) != -1)
  {
    return (get_existing(info));
  }
  else if ((info->msg_id = msgget(info->key, IPC_CREAT | SHM_R | SHM_W)) != -1)
  {
    return (get_creat(info));
  }
  else
  {
    return (error());
  }
}
