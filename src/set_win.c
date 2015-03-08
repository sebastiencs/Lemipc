/*
** set_win.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 17:47:02 2015 chapui_s
** Last update Sun Mar  8 17:52:02 2015 chapui_s
*/

#include "lemipc.h"

int		set_win(t_info *info, int *nb_free)
{
  (*nb_free) += 1;
  if (*nb_free >= RUN_TO_WIN)
  {
    set_connected(info, -(get_connected(info)));
    info->i_am_alive = 0;
    return (1);
  }
  return (0);
}
