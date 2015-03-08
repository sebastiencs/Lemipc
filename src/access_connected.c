/*
** access_connected.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 08:22:24 2015 chapui_s
** Last update Sun Mar  8 23:00:59 2015 chapui_s
*/

#include "lemipc.h"

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
