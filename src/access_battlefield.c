/*
** access_battlefield.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  8 08:23:51 2015 chapui_s
** Last update Sun Mar  8 08:24:18 2015 chapui_s
*/

#include "lemipc.h"

char		get_battlefield(t_info *info, int x, int y)
{
  char		tmp;

  x = (x < 0) ? (0) : (x % SIZE_X);
  y = (y < 0) ? (0) : (y % SIZE_Y);
  sem_lock(info);
  tmp = info->map[(y * SIZE_Y + x) % SIZE_MAP];
  sem_unlock(info);
  return (tmp);
}

void		set_battlefield(t_info *info, int x, int y, char value)
{
  x = (x < 0) ? (0) : (x % SIZE_X);
  y = (y < 0) ? (0) : (y % SIZE_Y);
  sem_lock(info);
  info->map[(y * SIZE_Y + x) % SIZE_MAP] = value;
  sem_unlock(info);
}
